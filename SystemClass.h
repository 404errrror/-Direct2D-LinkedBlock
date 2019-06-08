#pragma once

#include <Windows.h>
#include "InputClass.h"
#include "D2DClass.h"

class SystemClass
{
public:
	SystemClass	();
	SystemClass	(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Release();
	void WinLoop();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Update();
	void InitializeWindows();
	void ReleaseWindows();

	 
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	POINT m_screenRatio;
	
	D2DClass* m_D2D;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SystemClass* ApplicationHandle = nullptr;

const bool FULL_SCREEN = false;
