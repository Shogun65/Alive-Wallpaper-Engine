#pragma once

#include <d3d11.h>
#include <thread>
#include <atomic>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/hwcontext_d3d11va.h>
#include <libavutil/pixdesc.h>
}

class FFmpeg
{
public:

	void InitFFmpeg(const char* fileparth,
		ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int sizeofbuffer);

	static AVPixelFormat get_pix_format(
		AVCodecContext* CodecCtx,
		const AVPixelFormat* pix_fmt);

	~FFmpeg();

private:
	AVBufferRef* _HWDevice = nullptr;
	AVBufferRef* _HWFrame = nullptr;
	AVFormatContext* _FormatContext = nullptr;
	int _VideoStreamIndex = -1; // dont change this
	const AVCodec* _Codec = nullptr;
	AVCodecParameters* _CodecParameter = nullptr;
	AVCodecContext* _CodecContext = nullptr;

	/*
	*	This is going to run on deffrent thread. when it run when it stop?
	*	This Loop start when FFmpeginit func done!.	
	*	When it stop well when the Whole EXE (dll whatever) exit..
	*
	*/
	void RunDecoderLoop();
	std::thread T_RunDecoderLoop;
	std::atomic<bool> _DecodedThreadruning = true; // this is improtand
};

class FrameQueue
{
public:

	FrameQueue(int sizeofbuffer);
	~FrameQueue();


	int GetSizeofBuffer() const;
	AVFrame* pop();
	void push(AVFrame* Frame);

private:

	AVFrame** _Buffer; // AVFrame** that we useing to store the pointer of AVFrame*

	int _SizeofBuffer = 3; // A safe defualt well it not matter tho
	std::atomic<int> _Tail = 0;
	std::atomic<int> _Head = 0;

};