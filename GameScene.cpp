#include "stdafx.h"
#include "GameScene.h"
#include "D2DClass.h"

bool GameScene::Reatart = false;

GameScene::GameScene()
{
	m_pBackground = nullptr;
	m_pCameraTarget = nullptr;
	m_pGunSystem = nullptr;
	m_pFireWood = nullptr;
	m_pEnemySystem = nullptr;
}


GameScene::~GameScene()
{
}


void GameScene::Release()
{
	RELEASE(m_pBackground);
	RELEASE(m_pCameraTarget);
	RELEASE(m_pGunSystem);
	RELEASE(m_pFireWood);
	RELEASE(m_pCharacter);
	RELEASE(m_pEnemySystem);
}


int GameScene::Start()
{
	Reatart = false;
	m_isStart = true;
	m_isMask = true;
	g_screenMag = 1;
	D2DClass::handle->Resize();
	GameObject::SetRenderTarget(m_pBitmapRender);
	GameObject::SetMaskRender(m_pMaskRender);
	GameObject::SetUiRender(m_pUiRender);

	m_pBackground = new GameBackground();
	m_pBackground->Initialize();

	m_pCameraTarget = new CameraTarget();
	m_pCameraTarget->Initialize();

	m_pGunSystem = new GunSystem();
	m_pGunSystem->Initialize();

	m_pFireWood = new FireWood();
	m_pFireWood->Initialize();

	m_pCharacter = new Character();
	m_pCharacter->Initialize();

	m_pEnemySystem = new EnemySystem();
	m_pEnemySystem->Initialize();

	Camera::SetObject(m_pCameraTarget->GetComponentHub()->m_pTransform);

	SceneClass::StartComponent();
	Character::m_hp = 100;

	return 0;
}


int GameScene::Update()
{

	if (m_isStart == false)
		Start();
	Camera::CameraUpdate();

	m_pBitmapRender->BeginDraw();
	m_pBitmapRender->Clear(D2D1::ColorF(1, 1, 1));
	m_pMaskRender->BeginDraw();
	m_pMaskRender->Clear(D2D1::ColorF(1, 1, 1, 0));
	m_pUiRender->BeginDraw();
	m_pUiRender->Clear(D2D1::ColorF(1, 1, 1, 0));


	if (g_leftDown)
		m_pGunSystem->Shoot();
	if (g_pInput->isKeyDown('R'))
		m_pGunSystem->Reload();


	SceneClass::UpdateComponent();

	m_pBitmapRender->EndDraw();
	m_pMaskRender->EndDraw();
	m_pUiRender->EndDraw();
	SwapBuffer();

	if (g_pInput->isKeyDown('Z') || Reatart)
	{
		Release();
		Start();
	}
	return 0;
}


int GameScene::OnEvent(Event& event)
{
	return SceneClass::OnEvent(event);
}