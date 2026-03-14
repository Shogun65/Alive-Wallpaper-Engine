#include "Engine.h"
#include <cstdlib>

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE ignore, LPWSTR pCmdLine, int nCmdShow)
{
	// ignore this
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	Engine engine;

	engine.CreateWindowOnWorkerWAndRun(hInstance);
	
	return EXIT_SUCCESS;

}