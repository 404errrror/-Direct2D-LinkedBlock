#include "stdafx.h"
#include "SystemClass.h"


SystemClass::SystemClass()
{
	g_pInput = nullptr;
	m_D2D = nullptr;
}
SystemClass::SystemClass(const SystemClass&)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{

	InitializeWindows();

	g_pInput = new InputClass();
	if (!g_pInput)
	{
		//messageBox
		return false;
	}
	g_pInput->Initialize();

	m_D2D = new D2DClass();
	if (!m_D2D)
	{
		//MessageBox
		return false;
	}
	m_D2D->Initialize();


	return true;
}


void SystemClass::Release()
{
	RELEASE(m_D2D);

	DELETE(g_pInput);

	ReleaseWindows();
}


void SystemClass::WinLoop()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			done = true;
		else
		{
			result = Update();
			if (!result)
				done = true;
		}
	}
}


bool SystemClass::Update()
{
	//if (g_pInput->isKeyDown(VK_ESCAPE))
	//	return false;

	m_D2D->UpDate();

	return true;
}


void SystemClass::InitializeWindows()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY, screenWidth, screenHeight;


	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	// 어플리케이션의 이름
	m_applicationName = L"GameFrameWork";

	// 윈도우 클래스를 기본 설정으로 맞춥니다.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	// 모니터 화면 해상도.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 풀스크린 모드
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else
	{
		// 윈도우 크기 설정
		screenWidth = DEFALUT_SCREEN_WIDTH;
		screenHeight = DEFAULT_SCREEN_HEIGHT;

		// 창을 중앙에 배치
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	g_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		//WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		WS_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	ShowWindow(g_hwnd, SW_SHOW);
	SetForegroundWindow(g_hwnd);
	SetFocus(g_hwnd);
	UpdateWindow(g_hwnd);
	ShowCursor(true);

	return;
}


void SystemClass::ReleaseWindows()
{

	DestroyWindow(g_hwnd);
	g_hwnd = nullptr;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = nullptr;
	ApplicationHandle = nullptr;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg) {

	case WM_KEYDOWN: 
	{
		g_pInput->KeyDown((unsigned int)wparam);
		return 0;
	} 
	case WM_KEYUP:
	{ 
		g_pInput->KeyUp((unsigned int)wparam);
		return 0;
	} 
	
	case WM_LBUTTONDOWN:
	{
		g_leftDown = true;
		return 0;
	}
	case WM_LBUTTONUP:
	{
		g_leftDown = false;
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		CPoint mousePos;
		GetCursorPos(&mousePos);

		ScreenToClient(hwnd, &mousePos);

		if (g_pInput->isKeyDown('A'))
		{
			getchar();
		}


		g_mousePos.x = mousePos.x;
		g_mousePos.y = mousePos.y;

		
		g_mousePos.x = mousePos.x * g_screenRatioInv;
		g_mousePos.y = mousePos.y * g_screenRatioInv;

		g_mouseDesPos = Vector2::GetDesVector(g_mousePos);

		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		if (SceneManager::GetScene() == SceneManager::SCENE_START ||
			SceneManager::GetScene() == SceneManager::SCENE_SELECT
			)
			return 0;
		if ((int)wparam > 0)
		{
			if (g_screenMag < 5)
			{
				g_screenMag += g_screenMag * 0.1;
				m_D2D->Resize();
				Camera::InstantlySetting();
			}
		}
		else if ((int)wparam < 0)
		{
			if (g_screenMag > 0.05)
			{
				g_screenMag -= g_screenMag * 0.1;
				m_D2D->Resize();
				Camera::InstantlySetting();
			}
		}
		return 0;
	}
	case WM_SIZE:
	{
		if (m_D2D)
		{
			m_D2D->Resize();
		}
		return 0;
	}

	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam); 
	} 
	
	}

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_CREATE:
	{
		GetClientRect(hwnd, g_screenRect);
		break;
	}



	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}