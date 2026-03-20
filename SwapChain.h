#pragma once
#include <dxgi1_3.h>
#include <d3d11.h>
#include <wrl/client.h>
#pragma comment(lib,"dxgi.lib")

using Microsoft::WRL::ComPtr;

class SwapChin
{
public:

	void CreateSwapChin1(LONG Height, LONG Width, ID3D11Device* device);
	
	IDXGISwapChain1* GetSwapChin() const;

private:
	ComPtr<IDXGISwapChain1> _SwapChin = nullptr;
	ComPtr<IDXGIFactory2> _Factory = nullptr;
};