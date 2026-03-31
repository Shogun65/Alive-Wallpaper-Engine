#include "FFmpeg.h"
#include <algorithm>
/*
*	FrameQueue class in FFmpeg because of i dont want to have more pain
*	soo yea get whit it
* 
*/

void FrameQueue::init(int sizeofbuffer)
{
	_SizeofBuffer = std::clamp(sizeofbuffer, 3, 18);
	_StartThreshold = _SizeofBuffer;
	_Buffer = new AVFrame* [_SizeofBuffer];

	for(int i = 0; i < _SizeofBuffer; i++)
	{
		_Buffer[i] = nullptr;
	}
}

FrameQueue::~FrameQueue()
{
	for(int i = 0; i < _SizeofBuffer; i++)
	{
		av_frame_free(&_Buffer[i]);
	}
	delete[] _Buffer;
}

int FrameQueue::GetSizeofBuffer() const 
{
	printf("Queue size return: %d\n", _SizeofBuffer);
	return _SizeofBuffer;
}

bool FrameQueue::push(AVFrame* Frame)
{
	std::unique_lock<std::mutex> lock(_Mutex);
	
	_CondFull.wait(lock, [&]() 
	{ 
		return _BufferCount < (_SizeofBuffer - 1); // if Queue is full than wait
	});

	_Buffer[_Tail] = Frame; // put the frame pointer in Queue

	_Tail = (_Tail + 1) % _SizeofBuffer; // move the Tail 
	_BufferCount++; // Add when we get frame

	if(_Buffering && _StartThreshold >= _BufferCount)
	{
		_Buffering = false;
	}

	lock.unlock(); // before the notify_one!

	_CondEmpty.notify_one();

	return true; // dont matter😅
}

AVFrame* FrameQueue::pop()
{
	std::unique_lock<std::mutex> lock(_Mutex);

	_CondEmpty.wait(lock, [&]()
	{
		return (_BufferCount > 0) && (!_Buffering);
	});

	AVFrame* frame = _Buffer[_Head];

	_Head = (_Head + 1) % _SizeofBuffer;

	_BufferCount--;

	lock.unlock();

	_CondFull.notify_one();

	return frame;
}