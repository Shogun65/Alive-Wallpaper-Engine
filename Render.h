#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <dcomp.h>

class Render
{
public:

	void cleanscreen(ID3D11RenderTargetView* RTVOfBackBuffer, 
		IDXGISwapChain1* swapchin1, 
		ID3D11DeviceContext* devicecontext);




private:
	//idk
};