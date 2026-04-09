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

	double ptsSec = 0.0;
	AVFrame* POPFrame = FramePOP(ptsSec);

	if (!_ClockStarted) {
		QueryPerformanceFrequency(&_QpcFreq);
		QueryPerformanceCounter(&_QpcStart);
		_FirstPtsSec = ptsSec;
		_LastPtsSec = ptsSec;
		_ClockStarted = true;
	}

	// loop restart detect: pts jumps backwards
	if (ptsSec + 0.5 < _LastPtsSec) {
		QueryPerformanceCounter(&_QpcStart);
		_FirstPtsSec = ptsSec;
	}
	_LastPtsSec = ptsSec;

	LARGE_INTEGER now{};
	QueryPerformanceCounter(&now);

	double elapsedSec = double(now.QuadPart - _QpcStart.QuadPart) / double(_QpcFreq.QuadPart);
	double targetSec = ptsSec - _FirstPtsSec;
	double waitSec = targetSec - elapsedSec;

	if (waitSec > 0.0) {
		DWORD ms = (DWORD)(waitSec * 1000.0);
		if (ms > 0) Sleep(ms);
	}

	ProcessFrame(POPFrame);

	swapchin1->Present(1, 0);
	FrameReturn(POPFrame);
}