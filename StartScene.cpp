#include "stdafx.h"
#include "StartScene.h"
#include "D2DClass.h"

StartScene::StartScene()
{
	titleImage = nullptr;
	backgroundRect = nullptr;
	startBtn = nullptr;
	clippingEffect = nullptr;
	cameraTarget = nullptr;
	m_changing = false;
}


StartScene::~StartScene()
{
}


void StartScene::Release()
{
	titleImage->Release();
	delete titleImage;
	backgroundRect->Release();
	delete backgroundRect;
	RELEASE(startBtn)
	RELEASE(clippingEffect);
}


int StartScene::Start()
{
	m_isStart = true;
	g_screenMag = 1;
	D2DClass::handle->Resize();

	GameObject::SetRenderTarget(m_pBitmapRender);
	GameObject::SetMaskRender(m_pMaskRender);
	

	titleImage = new GameObject();
	titleImage->Initialize();
	titleImage->GetComponentHub()->AddComponent(ComponentHub::IMAGE);
	titleImage->GetComponentHub()->m_pImage->SetImage(g_hasher("TitleImg"));
	titleImage->GetComponentHub()->m_pTransform->SetPosition(Vector2(0, 300));

	backgroundRect = new GameObject();
	backgroundRect->Initialize();
	backgroundRect->GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);
	backgroundRect->GetComponentHub()->m_pRectRender->SetStrokeWidth(2);
	backgroundRect->GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(0.3, 0.3, 0.3, 0.5));
	backgroundRect->GetComponentHub()->m_pTransform->SetScale(Vector2(6.5, 6.5));
	backgroundRect->GetComponentHub()->m_pTransform->SetRotation(45);

	startBtn = new StartButton();
	startBtn->Initialize();

	clippingEffect = new CircleEffect();
	clippingEffect->Initialize();
	clippingEffect->SetScale(Vector2(21.9, 21.9));
	clippingEffect->SetTime(1.5);
	clippingEffect->SetType(CircleEffect::TYPE_MASK);
	clippingEffect->Play();

	cameraTarget = new GameObject();
	cameraTarget->Initialize();

	m_isMask = true;
	SceneClass::StartComponent();
	Camera::SetObject(cameraTarget->GetComponentHub()->m_pTransform);

	return 0;
}


int StartScene::Update()
{
	if (g_pInput->isKeyDown('R'))
	{
		Release();
		_CrtDumpMemoryLeaks();
		Start();
	}

	m_pBitmapRender->BeginDraw();
	m_pBitmapRender->Clear(D2D1::ColorF(1, 1, 1));
	m_pMaskRender->BeginDraw();
	m_pMaskRender->Clear(D2D1::ColorF(1, 1, 1, 0));

	Camera::CameraUpdate();

	if (m_isStart == false)
		Start();

	if (clippingEffect->IsPlay() == false)
		m_pMaskRender->Clear(D2D1::ColorF(1, 1, 1, 1));

	// 컴포넌트, 게임오브젝트 업뎃
	SceneClass::UpdateComponent();




	m_pBitmapRender->EndDraw();
	m_pMaskRender->EndDraw();
	SwapBuffer();

	if (startBtn->IsClicked())
	{
		if (m_changing == false)
		{
			m_changing = true;
			clippingEffect->SetScale(Vector2(30, 30), Vector2(0, 0));
			clippingEffect->GetComponentHub()->m_pTransform->SetPosition(g_mouseDesPos);
			clippingEffect->SetTime(0.8);
			clippingEffect->Play();
		}
		if (clippingEffect->GetComponentHub()->m_pTransform->GetScale().x <= 0)
		{
			// 씬 다시 불러올 것을 대비하여.
			m_isStart = false;
			m_changing = false;

			Release();
			SceneManager::SetScene(SceneManager::SCENE_SELECT);
		}
	}

	return 0;
}


int StartScene::OnEvent(Event& event)
{
	return SceneClass::OnEvent(event);
}