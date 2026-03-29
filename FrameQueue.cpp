#include "FFmpeg.h"
#include <algorithm>
/*
*	FrameQueue class in FFmpeg because of i dont want to have more pain
*	soo yea get whit it
* 
*/

// buffer or Queue whatever you like. IMPROTAND: it just store the avframe pointer in Queue
// not really frames. Frame are store is Pool ofc.. we just use it and free it. it fast
FrameQueue::FrameQueue(int sizeofbuffer) :
	_SizeofBuffer(std::clamp(sizeofbuffer, 3, 18)) // clamp it.. min is 3, max is 18
									// dont change unless you know what you doing (ofc😅)
{
	//delete on ~FrameQueue()
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