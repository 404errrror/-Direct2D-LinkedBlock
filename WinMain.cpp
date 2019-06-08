// DefenseGame.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "SystemClass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	
	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 2163;
	SystemClass* System;
	bool result;
	System = new SystemClass; 

	if(!System) {
		return 0; 
	} 

	result = System->Initialize(); 
	if(result) {
		System->WinLoop(); 

	}


	System->Release();
	delete System;
	System = nullptr; 
	return 0; 
}

