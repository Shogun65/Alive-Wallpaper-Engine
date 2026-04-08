template<typename FramePOPFunc, typename FrameReturnFunc, typename ProcessFrameFunc>
void Render::RenderFrame(
	ID3D11RenderTargetView* RTVOfBackBuffer,
	IDXGISwapChain1* swapchin1,
	ID3D11DeviceContext* devicecontext,
	FramePOPFunc FramePOP,
	FrameReturnFunc FrameReturn,
	ProcessFrameFunc ProcessFrame)
{

	float green_color[] = {0, 1, 0, 1};

	devicecontext->OMSetRenderTargets(
		1,
		&RTVOfBackBuffer,
		nullptr
		);

	devicecontext->ClearRenderTargetView(
		RTVOfBackBuffer,
		green_color
	);

	AVFrame* POPFrame = FramePOP();

	ProcessFrame(POPFrame);

	swapchin1->Present(1, 0);
	Sleep(1);//just for now
	FrameReturn(POPFrame);
}