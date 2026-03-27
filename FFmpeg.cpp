#include "FFmpeg.h"
#include <cstdlib>


/*
*	This
* 
* 
*/
void FFmpeg::InitFFmpeg(const char* fileparth, 
	ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	_HWDevice = av_hwdevice_ctx_alloc(AV_HWDEVICE_TYPE_D3D11VA);

	AVHWDeviceContext* HWDeviceCtx = (AVHWDeviceContext*)_HWDevice->data;

	AVD3D11VADeviceContext* d3d11DeviceContext = (AVD3D11VADeviceContext*)HWDeviceCtx->hwctx;

	d3d11DeviceContext->device = Device;
	d3d11DeviceContext->device_context = DeviceContext;

	if(av_hwdevice_ctx_init(_HWDevice) < 0)
	{
		MessageBoxW(nullptr, L"Error on av_hwdevice_ctx_init", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}
	else
	{
		printf("hwDevice init Done!\n");
	}

	if(avformat_open_input(&_FormatContext, fileparth, nullptr, nullptr) < 0)
	{
		MessageBoxW(nullptr, L"Error on avformat_open_input", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	if(avformat_find_stream_info(_FormatContext, nullptr) < 0)
	{
		MessageBoxW(nullptr, L"Error on avformat_find_stream_info", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	for(unsigned int i = 0; i < _FormatContext->nb_streams; i++)
	{
		if (_FormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			_VideoStreamIndex = i;
			break;
		}
	}
	
	if(_VideoStreamIndex == -1)
	{
		MessageBox(nullptr, L"_VideoStreamIndex still -1", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	_CodecParameter = _FormatContext->streams[_VideoStreamIndex]->codecpar;

	_Codec = avcodec_find_decoder(_CodecParameter->codec_id);

	_CodecContext = avcodec_alloc_context3(_Codec);

	avcodec_parameters_to_context(_CodecContext, _CodecParameter);

	_CodecContext->hw_device_ctx = _HWDevice;
	_CodecContext->get_format = get_pix_format;
	
	if (avcodec_open2(_CodecContext, _Codec, nullptr) < 0)
	{
		MessageBox(nullptr, L"Error on avcodec_open2", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}
	else
	{
		printf("FFmpeginit done!\n");
	}
}


/*
*
* 
* 
*/
AVPixelFormat FFmpeg::get_pix_format
(
	AVCodecContext* CodecCtx,
	const AVPixelFormat* pix_fmt
)
{
	for(const enum AVPixelFormat *p = pix_fmt; *p != AV_PIX_FMT_NONE; p++)
	{
		if(*p == AV_PIX_FMT_D3D11)
		{
			return *p;
		}
	}
	return pix_fmt[171]; // idk forcefuly return AV_PIX_FMT_D3D11 that is == to 171
}						// is that a good idea idk maybe?
