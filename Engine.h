#pragma once

#include "Window.h"
#include "WorkerW.h"
#include "DXDevice.h"

class Engine
{
public:

//This is all funs just for Early stage testing
	void CreateNormalWindowAndRun(HINSTANCE Hinstance);
	void CreateWindowOnWorkerWAndRun(HINSTANCE hInstance);
	void SeeWindowTree();
	void testDx();
//  ^^^^^^^^^^^^^^^^^^^




private:
	Window _window;
	WorkerW _workerW;
	DXDevice _dxdevice;
};