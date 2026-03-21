#include "SwapChain.h"
#include <iostream>

IDXGISwapChain1* SwapChin::GetSwapChin() const 
{
	return _SwapChin.Get();
}

void SwapChin::CreateSwapChin1(LONG Height, LONG Width, ID3D11Device* device)
{
	HRESULT hr;
	hr = CreateDXGIFactory2(0, __uuidof(IDXGIFactory2), (void**)_Factory.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Error on CreateDXGIFactory2", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	DXGI_SWAP_CHAIN_DESC1 scd = { };

	scd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	scd.BufferCount = 2;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	scd.Height = Height;
	scd.Width = Width;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

	hr = _Factory->CreateSwapChainForComposition(
		device,
		&scd,
		nullptr,
		_SwapChin.GetAddressOf()
	);

	if(FAILED(hr))
	{
		MessageBox(nullptr, L"Error on CreateSwapChainForComposition", L"Error", MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}
	else
	{
		printf("CreateSwapChainForComposition done!");
	}

}

