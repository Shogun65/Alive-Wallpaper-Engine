#pragma once

#include "Window.h"
#include "WorkerW.h"

class Engine
{
public:

//This is all funs just for Early stage testing
	void CreateNormalWindowAndRun(HINSTANCE Hinstance);
	void CreateWindowOnWorkerWAndRun(HINSTANCE hInstance);
	void SeeWindowTree();
//  ^^^^^^^^^^^^^^^^^^^




private:
	Window _window;
	WorkerW _workerW;
};