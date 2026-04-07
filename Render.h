#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <dcomp.h>

extern "C"
{
#include <libavcodec/avcodec.h>
}

class Render
{
public:

	// this is a test func
	void cleanscreen(ID3D11RenderTargetView* RTVOfBackBuffer, 
		IDXGISwapChain1* swapchin1, 
		ID3D11DeviceContext* devicecontext);

	template<typename FramePOPFunc, typename FrameReturnFunc, typename ProcessFrameFunc>
	void RenderFrame(
		ID3D11RenderTargetView* RTVOfBackBuffer,
		IDXGISwapChain1* swapchin1,
		ID3D11DeviceContext* devicecontext,
		FramePOPFunc FramePOP,
		FrameReturnFunc FrameReturn,
		ProcessFrameFunc ProcessFrame
		);


private:
	//idk
};
#include "Render.inl"