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

}