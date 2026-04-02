#include "FFmpeg.h"
#include <iostream>
// or size of buffer
// NOTE: Dont call this Func it going to get CALL by
// void FrameQueue::init func.
void FramePool::init(int sizeofqueue)
{
	for(int i = 0; i < sizeofqueue; i++)
	{
		printf("alloc AVFRAME!!\n");
		AVFrame* Frame = av_frame_alloc();
		_FramePool.push_back(Frame);
	}
}

AVFrame* FramePool::GetFrame()
{
	std::unique_lock<std::mutex> lock(_Mutex);

	_Cond.wait(lock, [&]()
	{
		return !_FramePool.empty();
	});

	std::cout << "getFrame called" << '\n';

	AVFrame* Frame = _FramePool.back();
	_FramePool.pop_back();

	return Frame;
}

void FramePool::ReturnFrame(AVFrame* frame)
{
	std::unique_lock<std::mutex> lock(_Mutex);

	av_frame_unref(frame);

	_FramePool.push_back(frame);
	printf("ReturnFrame called!\n");
	lock.unlock();

	_Cond.notify_one();
}
