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
		ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);

	static AVPixelFormat get_pix_format(
		AVCodecContext* CodecCtx,
		const AVPixelFormat* pix_fmt);

	~FFmpeg();

private:
	AVBufferRef* _HWDevice = nullptr;
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








private:




};