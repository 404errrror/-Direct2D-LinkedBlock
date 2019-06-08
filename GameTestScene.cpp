#include "stdafx.h"
#include "GameTestScene.h"
#include "D2DClass.h"
#include "SystemClass.h"
#include "StageSelector.h"


GameTestScene::GameTestScene()
{
	m_pTestEffect = nullptr;
	m_pMapCreator = nullptr;
	m_pCamTarget = nullptr;
	m_pSelectBtn = nullptr;
	m_pBackground = nullptr;
	m_changing = false;
	m_rDowned = false;
	m_isClear = false;
	m_selectClicked = false;
}


GameTestScene::~GameTestScene()
{
}


void GameTestScene::Release()
{
	//myCharacter->Release();
	//myCharacter2->Release();
	//destBlockArr[1]->Release();
	//destBlockArr[0]->Release();
	m_pTestEffect->Release();
	m_pMapCreator->Release();
	m_pCamTarget->Release();
	m_pClearImage->Release();
	delete m_pClearImage;
	m_pSelectBtn->Release();
	m_pBackground->Release();
}


int GameTestScene::Start()
{
	_CrtDumpMemoryLeaks();
	m_isStart = true;
	m_isMask = true;
	m_changing = false;
	m_isClear = false;

	g_screenMag = 0.6;
	D2DClass::handle->Resize();
	ApplicationHandle->MessageHandler(g_hwnd,WM_MOUSEMOVE,0,0);

	GameObject::SetRenderTarget(m_pBitmapRender);
	GameObject::SetMaskRender(m_pMaskRender);

	// 배경화면 파티클
	m_pBackground = new BackgroundParticle();
	m_pBackground->Initialize();
	m_pBackground->SetAmount(200);
	m_pBackground->Generate();

	// 맵
	char filePath[64];
	sprintf_s(filePath, "MapData\\%d.txt", StageSelector::GetStage());
	m_pMapCreator = new MapCreator();
	m_pMapCreator->ReadMap(filePath);
	m_pMapCreator->CreateMap();

	// 게임에는 시작애니메이션 안넣을려고 했는데 넣어도 나름 괜찮은듯?
	m_pTestEffect = new CircleEffect();
	m_pTestEffect->Initialize();
	m_pTestEffect->SetScale(Vector2(0,0),Vector2(50, 50));
	m_pTestEffect->SetTime(1.5);
	m_pTestEffect->SetType(CircleEffect::TYPE_MASK);
	m_pTestEffect->Play();
	
	// 카메라
	m_pCamTarget = new CameraTarget();
	m_pCamTarget->Initialize();
	m_pCamTarget->RefreshTarget();

	// 클리어 화면
	m_pClearImage = new GameObject();
	m_pClearImage->Initialize();
	m_pClearImage->GetComponentHub()->AddComponent(ComponentHub::IMAGE);
	m_pClearImage->GetComponentHub()->AddComponent(ComponentHub::SHAPE_ANIMATION);
	m_pClearImage->GetComponentHub()->m_pImage->SetImage(g_hasher("StageClear"));
	m_pClearImage->GetComponentHub()->m_pShapeAnimation->SetScale(Vector2(0, 0), Vector2(1, 1));
	m_pClearImage->GetComponentHub()->m_pShapeAnimation->SetTime(0.5);
	m_pClearImage->GetComponentHub()->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);
	m_pClearImage->SetActive(false);

	// 클리어후 선택버튼
	m_pSelectBtn = new ClearSelectButton();
	m_pSelectBtn->Initialize();
	m_pSelectBtn->GetComponentHub()->m_pTransform->SetParent(m_pClearImage->GetComponentHub()->m_pTransform);

	m_pBackground->SetCamera(m_pCamTarget->GetComponentHub()->m_pTransform);


	SceneClass::StartComponent();



	_CrtDumpMemoryLeaks();
	return 0;
}


int GameTestScene::Update()
{

	if (m_isStart == false)
		Start();


	Camera::CameraUpdate();
	// 클리핑효과 카메라 위치에 주기
	if(m_pTestEffect->IsPlay())
		m_pTestEffect->GetComponentHub()->m_pTransform->SetPosition(m_pCamTarget->GetComponentHub()->m_pTransform->GetPosition());

	m_pBitmapRender->BeginDraw();
	m_pBitmapRender->Clear(D2D1::ColorF(1, 1, 1));
	m_pMaskRender->BeginDraw();
	m_pMaskRender->Clear(D2D1::ColorF(1, 1, 1,0));

	if (m_pTestEffect->IsPlay() == false)
		m_pMaskRender->Clear(D2D1::ColorF(1, 1, 1, 1));

	// 컴포넌트, 게임오브젝트 업뎃
	SceneClass::UpdateComponent();

	// 클리어 체크.
	if (ClearCheck() && m_isClear == false)
	{
		m_isClear = true;
		m_pClearImage->SetActive(true);
		m_pClearImage->GetComponentHub()->m_pShapeAnimation->SetScale(Vector2(0, 0), Vector2(1 / g_screenMag, 1 / g_screenMag));
		m_pClearImage->GetComponentHub()->m_pShapeAnimation->Play();
		m_pClearImage->GetComponentHub()->m_pTransform->SetPosition(m_pCamTarget->GetComponentHub()->m_pTransform->GetPosition());

		m_pSelectBtn->SetActive(true);
		m_pSelectBtn->GetComponentHub()->m_pShapeAnimation->Play();
	}


	m_pBitmapRender->EndDraw();
	m_pMaskRender->EndDraw();

	SwapBuffer();

	if (g_pInput->isKeyDown(KEY_TAB))
		m_pCamTarget->ChangeNextTarget();


	if (
		g_pInput->isKeyDown('R') || 
		g_pInput->isKeyDown(VK_ESCAPE)||
		m_pSelectBtn->IsClicked()
		)
	{
		if (m_changing == false)
		{
			if (g_pInput->isKeyDown('R'))
				m_rDowned = true;
			else if (m_pSelectBtn->IsClicked() || g_pInput->isKeyDown(VK_ESCAPE))
				m_selectClicked = true;
			m_changing = true;

			m_pTestEffect->SetScale(Vector2(30, 30), Vector2(0, 0));
			m_pTestEffect->GetComponentHub()->m_pTransform->SetPosition(m_pCamTarget->GetComponentHub()->m_pTransform->GetPosition());
			m_pTestEffect->SetTime(0.8);
			m_pTestEffect->Play();
		}

	}

	if (m_pTestEffect->GetComponentHub()->m_pTransform->GetScale().x <= 0)
	{
		Release();
		m_changing = false;

		if (m_rDowned == true)
		{
			m_rDowned = false;
			_CrtDumpMemoryLeaks();
			Start();
		}
		else if (m_selectClicked)
		{
			m_selectClicked = false;
			m_isStart = false;
			StageSelector::SetStage(0);
			SceneManager::SetScene(SceneManager::SCENE_SELECT);
		}
	
	}


	return 0;
}


int GameTestScene::OnEvent(Event& event)
{
	return SceneClass::OnEvent(event);
}


bool GameTestScene::ClearCheck()
{
	// 중간에 검사해서 다음 씬으로 바꾸어버리면 현재 씬이 실행 중간에 릴리즈를 해버림.
	// --------------------> Moved 이벤트가 가끔 무시될 때가 있어서 매 프레임 검사하고 있음. 나중에 수정
	for (std::list<DestBlock*>::iterator it = DestBlock::list.begin(); it != DestBlock::list.end(); ++it)
	{
		if ((*it)->IsDest() == false)
			return false;
	}
	return true;
}