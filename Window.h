#pragma once
#include <windows.h>

class Window
{
public:

	//This Create Main window that get Parent whit WorkerW
	// Call this Funs after FindWorkerW_T(if you want to make this class child of WorkerW 
	// if not you can skip that WorkerW)
	// and before MessageLoopRun()
	// NOTE: This Funs also Make Window Class and RegisterClass to!
	bool CreateMainWindow(HINSTANCE hInstance);

	//This run the message loop. For Window and
	// Inside this Message loop you going to Render Frames too
	//
	void MessageLoopRun();

	// As the name say it Enable Debug Console
	// why we need debug Console because we really not going to use
	// MessageBoxW. Debug Console is better(in my mind hehe). How to use it simple
	// just use printf or wprintf easy as that.
	void InitDebugConsole();

	// This Funs get Call by Widows not by as. If some event happand
	//We just use this as Handel some event (like WM_DESTORY etc)
	//Other Even Window can Handel it by (DefWindowProc)
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	//This Funs Attach Hwnd (our mainwindow) to workerW
	//Call this Funs after WorkerW found. and before CreateMainWindow funs
	void AttachHwndToWorkerW(HWND WorkerW);

	void ShowMainWindow();

	// Cmom really you need to know what this two do
	HWND GetHWND() const;

private:
	// This is Our Window not a WorkerW Window
	HWND _hwnd = nullptr;
};
