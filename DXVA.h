#pragma once
#include <d3d11.h>
#include<wrl/client.h>

extern "C"
{
#include <libavcodec/avcodec.h>
}

using Microsoft::WRL::ComPtr;

class DXVA
{
public:

	/**
	*	Call this Func After DX and Swapchin are done.
	*	
	*	This func take care of most of createing stuff and init. so you 
	*	dont need to worry much about init and createing stuff by your self.
	*/
	void InitDXVA(
		ID3D11Device* Device,
		ID3D11DeviceContext* DeviceContext,
		ID3D11Texture2D* BackBuffer
		);
	/**
	*	This Func Process the AVFrame that we pop in render than
	*	render that frame on backbuffer than we can persent!
	*/
	void ProcessFrame(AVFrame* POPFrame);

private:
	ComPtr<ID3D11VideoDevice> _VideoDevice = nullptr;
	ComPtr<ID3D11VideoContext> _VideoContext = nullptr;
	ComPtr<ID3D11VideoProcessor> _VideoProcessor = nullptr;
	ComPtr<ID3D11VideoProcessorEnumerator> _VideoProcessorEnum = nullptr;
	ComPtr<ID3D11VideoProcessorInputView> _VideoInputView = nullptr;
	ComPtr<ID3D11VideoProcessorOutputView> _VideoOutputView = nullptr;

	void CreateOutputView(ID3D11Device* Device,
		ID3D11DeviceContext* DeviceContext);

	void InitVideoDeviceAndContext();

	ID3D11VideoProcessorInputView* GetInputView(AVFrame* POPFrame);
	
};
