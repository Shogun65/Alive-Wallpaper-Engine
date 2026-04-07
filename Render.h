#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <dcomp.h>

class Render
{
public:

	// this is a test func
	void cleanscreen(ID3D11RenderTargetView* RTVOfBackBuffer, 
		IDXGISwapChain1* swapchin1, 
		ID3D11DeviceContext* devicecontext);

	template<typename FramePOPFunc, typename FrameReturnFunc>
	void RenderFrame(
		ID3D11RenderTargetView* RTVOfBackBuffer,
		IDXGISwapChain1* swapchin1,
		ID3D11DeviceContext* devicecontext,
		FramePOPFunc FramePOP,
		FrameReturnFunc FrameReturn);


private:
	//idk
};
#include "Render.inl"