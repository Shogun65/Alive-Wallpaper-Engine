#include "WorkerW.h"
#include <iostream>
#include <cstdlib>

//Return WorkerW
HWND WorkerW::GetWorkerW() const
{
	return _WorkerW;
}

//return Progman
HWND WorkerW::GetProgman() const
{
	return _Progman;
}  

//Okay it Spawn WorkerW you know but where there is Three Sentmessage
//Because on older system we may need to Sent wparam like this 0xD and
//lparam like 0 and 1 but in newer system we can just sent wparam 0 and lparam 0
//And it Work fine too
void WorkerW::SpawnWorkerW()
{
	_Progman = FindWindow(L"Progman", nullptr);

	SendMessageTimeout(
		_Progman,
		0x052C,
		0,
		0,
		SMTO_NORMAL,
		1000,
		nullptr
	);

	SendMessageTimeout(
		_Progman,
		0x052C,
		0xD,
		1,
		SMTO_NORMAL,
		1000,
		nullptr
	);

	SendMessageTimeout(
		_Progman,
		0x052C,
		0xD,
		0,
		SMTO_NORMAL,
		1000,
		nullptr
	);


}

void WorkerW::FindWorkerW()
{
	printf("Runing _T1!\n");
	EnumChildWindows(_Progman, FindWorkerW_T1, (LPARAM)this);
	printf("Done Runing _T1\n");
	if(_WorkerW == nullptr)
	{
		printf("Finding WorkerW fail by _T1\n");
		printf("Trying on _T2\n");
		EnumWindows(FindWorkerW_T2, (LPARAM)this);
		printf("Done Runing _T2\n");
	}

	if(_WorkerW == nullptr)
	{
		MessageBox(nullptr, L"Cant Find WorkerW", L"Error WorkerW", MB_ICONERROR);
		std::exit(EXIT_SUCCESS);
	}
}


BOOL CALLBACK WorkerW::FindWorkerW_T1(HWND hwnd, LPARAM lparam)
{
	WorkerW* self = (WorkerW*)lparam;

	wchar_t WindowName_[512];
	
	GetClassName(hwnd, WindowName_, sizeof(WindowName_));
	
	if(wcscmp(WindowName_, L"WorkerW") == 0)
	{
		HWND maybeWorkerW = FindWindowExW(hwnd, nullptr, L"SHELLDLL_DefView", nullptr);
		printf("HWND: %p , maybeWorkerW: %ws\n", hwnd, WindowName_);
		// Let me say whats going on here..
		// we chack WorkerW if it have SHELLDLL_DefView if it have than we skip it
		// because we want a workerW who child of progman and also Empty
		// SO we chack if maybeWorkerW is NULL or not.. if it NULL than mean its empty
		// Thats the WorkerW we want 
		if(!maybeWorkerW)
		{
			self->_WorkerW = hwnd;
			printf("WorkerW found! by _T1\n");
			printf("HWND: %p , WorkerW: %ws\n", hwnd, WindowName_);
			return false;
		}
	}
	return true;
}

BOOL CALLBACK WorkerW::FindWorkerW_T2(HWND hwnd, LPARAM lparam)
{
	WorkerW* self = (WorkerW*)lparam;

	wchar_t WindowName_[1024];

	GetClassName(hwnd, WindowName_, sizeof(WindowName_));

	if (wcscmp(WindowName_, L"WorkerW") == 0)
	{
		HWND WorkerWParent = GetParent(hwnd);

		/*
		* Now you aksing your self why chack hwnd Parent on _T2 but now in _T1
		* Remember that we call _T1 by EnumChildWindows(_Progman, ...)
		* Yes that means give every window that is child of Progman
		* But some Windows version. program child are Not under him so we need
		* to see top level window but in top level there are many other WorkerW
		* So we Chack if this WorkerW are child of progman or not than we chack if it
		* have SHELLDLL_DefView or not if not than and also this workerW is child of
		* Program thats the WorkerW we want.
		*/
		if(WorkerWParent != self-> _Progman)
		{
			return true;
		}

		HWND maybeWorkerW = FindWindowExW(hwnd, nullptr, L"SHELLDLL_DefView", nullptr);
		printf("HWND: %p , maybeWorkerW: %ws\n", hwnd, WindowName_);
		// Let me say whats going on here..
		// we chack WorkerW if it have SHELLDLL_DefView if it have than we skip it
		// because we want a workerW who child of progman and also Empty
		// SO we chack if maybeWorkerW is NULL or not.. if it NULL than mean its empty
		// Thats the WorkerW we want 
		if (!maybeWorkerW)
		{
			self->_WorkerW = hwnd;
			printf("WorkerW found! by _T2\n");
			printf("HWND: %p , WorkerW: %ws\n", hwnd, WindowName_);
			return false;
		}
	}
	return true;

}

//This Funs mainly for testing ignore this
void WorkerW::PrintWindowThree()
{
	EnumWindows(WindowTree, 0);
	printf("Child EnumChildWindows\n");
	EnumChildWindows(_Progman, WindowTree, 0);
}


BOOL CALLBACK WorkerW::WindowTree(HWND hwnd, LPARAM lparam)
{
	wchar_t classnames[1024];

	GetClassNameW(hwnd, classnames, sizeof(classnames));

	printf("HWND: %p , ClassNames: %ws\n", hwnd, classnames);

	return true;
}