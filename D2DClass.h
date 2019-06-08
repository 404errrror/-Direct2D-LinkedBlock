#pragma once
#include "TestScene.h"
#include "GameTestScene.h"
class D2DClass
{
public:
	D2DClass();
	~D2DClass();

	void Initialize();
	void Release();

	void UpDate();
	void Resize();

	static void						SetSolidBrush();
	static ID2D1SolidColorBrush*	GetSolidBrush(D2D1_COLOR_F color);
	static ID2D1Factory* m_pFactory;
	static D2DClass* handle;
private:
	
	static ID2D1HwndRenderTarget *m_pRenderTarget;
	static IDWriteFactory *m_pWriteFactory;

	static ID2D1SolidColorBrush* m_pRedBrush;
	static ID2D1SolidColorBrush* m_pGreenBrush;
	static ID2D1SolidColorBrush* m_pBlueBrush;

	//SceneClass* testScene = new TestScene();
	//SceneClass* gameTestScene = new GameTestScene();
};
