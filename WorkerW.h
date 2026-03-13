#pragma once
#include <windows.h>

class WorkerW
{
public:

	/*
	* This Funs call FindWorkerW_T1 and so on..
	* And this Funs also handel if _T1 fails than it 
	* Run _T2 so on.. Until it find workerW if he unable to find workerW
	* than i dont know what to do it just thow a Error Messagebox one okay
	* And exit Progman thats it
	*/
	void FindWorkerW();

	/*
	* About this Funs ahh it just for some testing stuff
	* you can ignore this funs
	*/
	void PrintWindowThree();

	//This Funs Seen Message to progman and Spawn WorkerW
	void SpawnWorkerW();

	HWND GetWorkerW() const;
	HWND GetProgman() const;

private:
	HWND _Progman = nullptr;
	HWND _WorkerW = nullptr;

	//This Funs Find WorkerW and if it Success to find WorkerW
	//Than it set it to _WorkerW. And _T1 means that you going to
	//Run this Funs first. than if chack if This finder find WorkerW or not
	//If not than Than Run FindWorkerW_T2 and so on..
	//IMPROTAND: Call this funs After SpawnWorkerW() funs
	static BOOL CALLBACK FindWorkerW_T1(HWND hwnd, LPARAM lparam);
	static BOOL CALLBACK FindWorkerW_T2(HWND hwnd, LPARAM lparam);
	static BOOL CALLBACK WindowTree(HWND hwnd, LPARAM lparam);
};

