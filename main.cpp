#include "Engine.h"
#include <cstdlib>

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE ignore, LPWSTR pCmdLine, int nCmdShow)
{
	// ignore this
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	Engine engine;

	const char* fileparth = "C:/Users/gmy87/Downloads/ayanami-rei-beneath-blue-light.3840x2160.mp4";



	engine.MakeWindowRunwhitWorkerWandRunDXandswapchinWhitFFmpeg(hInstance,
		fileparth);
	
	return EXIT_SUCCESS;

}