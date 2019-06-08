#include "stdafx.h"
#include "D2DClass.h"

D2DClass* D2DClass::handle;

ID2D1Factory* D2DClass::m_pFactory;
ID2D1HwndRenderTarget* D2DClass::m_pRenderTarget;
IDWriteFactory* D2DClass::m_pWriteFactory;

ID2D1SolidColorBrush* D2DClass::m_pRedBrush;
ID2D1SolidColorBrush* D2DClass::m_pGreenBrush;
ID2D1SolidColorBrush* D2DClass::m_pBlueBrush;

D2DClass::D2DClass()
{
	m_pRenderTarget = nullptr;
	handle = this;
}


D2DClass::~D2DClass()
{
}


void D2DClass::Initialize()
{
	HRESULT hr;

	// Factory, RenderTarget 초기화.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"D2DClass::Initialize()\nFactory 생성에 실패했습니다.", 
			L"D2D1CreawteFactory",
			MB_ICONERROR
			);
		return;
	}


	//윈도우 창틀 크기계산. -> 화면 전체 좌표를 계산하기 위해.
	CRect clientRect;
	CRect windowRect;
	GetClientRect(g_hwnd, clientRect);
	GetWindowRect(g_hwnd, windowRect);
	g_windowRight = (windowRect.Width() - clientRect.Width());
	g_windowTop = windowRect.Height() - clientRect.Height();		//왼쪽 오른쪽 아랫쪽의 창틀 크기는 같으므로.

	// 화면 배율 설정.
	g_screenMag = 0.6;
	//화면 비율 계산, RenderTarget 생성.
	Resize();


	if (m_pRenderTarget->GetAntialiasMode() == D2D1_ANTIALIAS_MODE_ALIASED)
		m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		///////// ----------> 나중에 시스템 클래스 구현해서 게임설정파일로 부터 읽어서 설정하기.


	// Text Format 초기화.				------------> 나중에 텍스트 클래스로 따로 빼기.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pWriteFactory));

	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"D2DCalss::Initialize()\nDWriteFactory 생성에 실패했습니다.",
			L"DWriteCreateFactory",
			MB_ICONERROR
			);
		return;
	}


	// COM라이브러리를 사용하기 위해서 COM라이브러리를 초기화. WIC 사용하기 위해.
	CoInitialize(NULL);

	//testScene->Initialize(m_pRenderTarget);
	//gameTestScene->Initialize(m_pRenderTarget);
	SceneManager::Initialize(m_pRenderTarget);
	SceneManager::SetScene(SceneManager::SCENE_START);
	BitmapTable::Initialize(m_pRenderTarget);
	Time::Initialize();
}

void D2DClass::Release()
{
	
	RELEASE(m_pRenderTarget);
	m_pWriteFactory->Release();

	delete this;
}


void D2DClass::UpDate()
{

	Time::Refresh();
	//if (FAILED(gameTestScene->Update()))
	if (FAILED(SceneManager::Update()))
	{
		MessageBox(g_hwnd, L"D2DClass::Update()\nTestScene->Update() Error.", L"testScene->Update()", MB_ICONERROR);
	}



	///////////////Scene클래스 만들고 BeginScene, EndScene만들기.
}


/// --------------> 메모리누수
void D2DClass::Resize()
{
	HRESULT hr;

	GetClientRect(g_hwnd, g_screenRect);
	RELEASE(m_pRenderTarget);

	hr = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			g_hwnd,
			D2D1::SizeU(g_screenRect.right, g_screenRect.bottom)
			),
		&m_pRenderTarget
		);

	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"D2DClass::Resize()\nCreate RenderTarget Failed.",
			L"CreateHwndRenderTarget",
			MB_ICONERROR
			);
	}

	g_screenWidthRatio = (float)g_screenRect.Width() / (MAX_SCREEN_WIDTH - g_windowRight);
	g_screenHeightRatio = (float)g_screenRect.Height()/ (MAX_SCREEN_HEIGHT - g_windowTop);

	g_screenWidthRatio > g_screenHeightRatio ?
		g_screenRatio = g_screenHeightRatio :
		g_screenRatio = g_screenWidthRatio;

	// 화면 배율(x100% 같은거) 설정
	g_screenRatio *= g_screenMag;
	//역수 설정.
	g_screenRatioInv = 1 / g_screenRatio;

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(
		D2D1::SizeF(g_screenRatio, g_screenRatio),
		D2D1::Point2F(0, 0))
		);
	SetSolidBrush();
	m_pRenderTarget->GetTransform(&g_defaultMatrix);

	BitmapTable::Initialize(m_pRenderTarget);

	SceneManager::OnEvent(ScreenResizeEvent(m_pRenderTarget));

	Camera::InstantlySetting();
}



void D2DClass::SetSolidBrush()
{
	RELEASE(m_pRedBrush);
	RELEASE(m_pGreenBrush);
	RELEASE(m_pBlueBrush);

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 0, 0), &m_pRedBrush);
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 1, 0), &m_pGreenBrush);
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 1), &m_pBlueBrush);
}
ID2D1SolidColorBrush* D2DClass::GetSolidBrush(D2D1_COLOR_F color)
{
	if (color.r == 1 && color.g == 0 && color.b == 0)
		return m_pRedBrush;
	else if (color.r == 0 && color.g == 1 && color.b == 0)
		return m_pGreenBrush;
	else if (color.r == 0 && color.g == 0 && color.b == 1)
		return m_pBlueBrush;
	else
		return nullptr;
}