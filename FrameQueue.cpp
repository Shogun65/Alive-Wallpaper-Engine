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