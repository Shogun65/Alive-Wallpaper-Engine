#pragma once
#include <d3d11.h>
#include<wrl/client.h>

using Microsoft::WRL::ComPtr;

class DXVA
{
public:







private:
	ComPtr<ID3D11VideoDevice> _VideoDevice = nullptr;
	ComPtr<ID3D11VideoContext> _VideoContext = nullptr;

};