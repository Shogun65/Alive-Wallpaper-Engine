#include "Engine.h"
#include <cstdlib>
/*

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

*/
int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE ignore, LPWSTR pCmdLine, int nCmdShow)
{
	// ignore this
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	Engine engine;

	engine.testDx();
	
	return EXIT_SUCCESS;

}