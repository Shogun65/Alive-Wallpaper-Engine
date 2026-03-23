#include "Engine.h"

void Engine::CreateNormalWindowAndRun(HINSTANCE hInstance)
{
	_window.InitDebugConsole();
	_window.CreateMainWindow(hInstance);
	_window.ShowMainWindow();
	//_window.MessageLoopRun();
}

void Engine::CreateWindowOnWorkerWAndRun(HINSTANCE hInstance)
{
	_window.InitDebugConsole();
	_window.CreateMainWindow(hInstance);
	_workerW.SpawnWorkerW();
	_workerW.FindWorkerW();
	_window.AttachHwndToWorkerW(_workerW.GetWorkerW());
	_window.ShowMainWindow();
	//_window.MessageLoopRun();
}

void Engine::SeeWindowTree()
{
	_window.InitDebugConsole();
	_workerW.SpawnWorkerW();
	_workerW.PrintWindowThree();
}

void Engine::testDx()
{
	_window.InitDebugConsole();
	_dxdevice.CreateDeviceAndDeviceContext();
}

void Engine::testDXandSwapchin(HINSTANCE hInstance)
{
	_window.InitDebugConsole();
	_window.CreateMainWindow(hInstance);
	_dxdevice.CreateDeviceAndDeviceContext();

	_swapchin.CreateSwapChin1(
		_window.GetWindowHeight(),
		_window.GetWindowWidth(),
		_dxdevice.GetDevice());
}

void Engine::testDXandswapanddcomp(HINSTANCE hInstance)
{
	_window.InitDebugConsole();
	_window.CreateMainWindow(hInstance);
	_dxdevice.CreateDeviceAndDeviceContext();

	_swapchin.CreateSwapChin1(
		_window.GetWindowHeight(),
		_window.GetWindowWidth(),
		_dxdevice.GetDevice());
	_swapchin.CreateRTVForBackBuffer(_dxdevice.GetDevice(), _dxdevice.GetDeviceContext());
	_DComp.CreateDComp(_window.GetHWND(), _swapchin.GetSwapChin(), _dxdevice.GetDevice());

}

void Engine::MakeWindowRunwhitWorkerWandRunDXandswapchin(HINSTANCE hInstance)
{
	_window.InitDebugConsole();
	_window.CreateMainWindow(hInstance);
	_workerW.SpawnWorkerW();
	_workerW.FindWorkerW();
	_window.AttachHwndToWorkerW(_workerW.GetWorkerW());
	_dxdevice.CreateDeviceAndDeviceContext();
	_swapchin.CreateSwapChin1(
		_window.GetWindowHeight(),
		_window.GetWindowWidth(),
		_dxdevice.GetDevice());
	_swapchin.CreateRTVForBackBuffer(_dxdevice.GetDevice(), _dxdevice.GetDeviceContext());
	_DComp.CreateDComp(_window.GetHWND(), _swapchin.GetSwapChin(), _dxdevice.GetDevice());
	_window.ShowMainWindow();
	
	_window.MessageLoopRun([&]() {_render.cleanscreen(_swapchin.GetRTVOfBackBuffer(), _swapchin.GetSwapChin(), _dxdevice.GetDeviceContext()); });
	
}