#pragma once

#include <d3d11.h>
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

	static enum AVPixelFormat get_pix_format(
		AVCodecContext* CodecCtx,
		const AVPixelFormat* pix_fmt);

private:
	AVBufferRef* _HWDevice = nullptr;
	AVFormatContext* _FormatContext = nullptr;
	int _VideoStreamIndex = 0;
	const AVCodec* _Codec = nullptr;
	AVCodecParameters* _CodecParameter = nullptr;
	AVCodecContext* _CodecContext = nullptr;
};