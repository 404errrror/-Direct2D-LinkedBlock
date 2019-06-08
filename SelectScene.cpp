#include "stdafx.h"
#include "SelectScene.h"
#include "D2DClass.h"
#include "StageSelector.h"


SelectScene::SelectScene()
{
	m_titleImg = nullptr;
	clippingEffect = nullptr;
	m_changing = false;
	m_escape = false;
}


SelectScene::~SelectScene()
{
}


void SelectScene::Release()
{
	RELEASE(clippingEffect);

	for (int i = 0; i < 6; i++)
		m_stageBtn[i]->Release();
	delete[] m_stageBtn;
	m_titleImg->Release();
	delete m_titleImg;
}


int SelectScene::Start()
{
	m_isStart = true;
	m_escape = false;
	g_screenMag = 1;
	D2DClass::handle->Resize();

	GameObject::SetRenderTarget(m_pBitmapRender);
	GameObject::SetMaskRender(m_pMaskRender);

	m_titleImg = new GameObject();
	m_titleImg->Initialize();
	m_titleImg->GetComponentHub()->AddComponent(ComponentHub::IMAGE);
	m_titleImg->GetComponentHub()->m_pImage->SetImage(g_hasher("SelectStageImg"));
	m_titleImg->GetComponentHub()->m_pTransform->SetPosition(Vector2(0, 300));

	clippingEffect = new CircleEffect();
	clippingEffect->Initialize();
	clippingEffect->SetScale(Vector2(22, 22));
	clippingEffect->SetTime(1.5);
	clippingEffect->SetType(CircleEffect::TYPE_MASK);
	clippingEffect->Play();

	m_stageBtn = new StageButton*[6];
	for (int i = 0; i < 6; ++i)
	{
		m_stageBtn[i] = new StageButton();
		// 초기화할 때 스테이지 값이 필요하므로 initialize하기전에 호출해주기.
		m_stageBtn[i]->SetStage(i+1);
		m_stageBtn[i]->Initialize();
		m_stageBtn[i]->GetComponentHub()->m_pTransform->SetPosition(Vector2(-260 + i * 100, 0));
	}


	m_isMask = true;
	SceneClass::StartComponent();

	return 0;
}


int SelectScene::Update()
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


	if (StageSelector::GetStage() != 0 ||
		g_pInput->isKeyDown(VK_ESCAPE)
		)
	{
		if (m_changing == false)
		{
			if (g_pInput->isKeyDown(VK_ESCAPE))
			{
				clippingEffect->GetComponentHub()->m_pTransform->SetPosition(Vector2(0,0));
				m_escape = true;
			}
			else
				clippingEffect->GetComponentHub()->m_pTransform->SetPosition(g_mouseDesPos);
			m_changing = true;
			clippingEffect->SetScale(Vector2(30, 30), Vector2(0, 0));
			clippingEffect->SetTime(0.8);
			clippingEffect->Play();
		}
	
	}
	if (clippingEffect->GetComponentHub()->m_pTransform->GetScale().x <= 0)
	{
		m_isStart = false;
		m_changing = false;
		Release();
		if (StageSelector::GetStage() != 0)
			SceneManager::SetScene(SceneManager::SCENE_GAME_TEST);
		else if (m_escape)
			SceneManager::SetScene(SceneManager::SCENE_START);
	}


	return 0;
}


int SelectScene::OnEvent(Event& event)
{
	return SceneClass::OnEvent(event);
}