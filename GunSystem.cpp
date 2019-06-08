#include "stdafx.h"
#include "GunSystem.h"


GunSystem::GunSystem()
{
	m_screenSize = Vector2();
	m_pShootPoint = nullptr;
	m_pCountText = nullptr;
	m_pGunPtr = nullptr;
	m_shootLock = false;
	m_reloadDown = false;
	m_showInfoText = false;
	m_infoTextTime = 0;
	m_infoType = NONE;

	m_pRestartBtn = nullptr;
}


GunSystem::~GunSystem()
{
}


void GunSystem::Initialize()
{
	GameObject::Initialize();
	m_isUi = true;
	m_pGunPtr = &m_defaultGun;
	//m_pComponentHub->AddComponent(ComponentHub::IMAGE);

	m_pShootPoint = new ShootPoint();
	m_pShootPoint->Initialize();

	m_pCountText = new GameObject();
	m_pCountText->Initialize();

	m_pInfoText = new GameObject();
	m_pInfoText->Initialize();

	m_pRestartBtn = new GameRestartBtn();
	m_pRestartBtn->Initialize();

	m_screenSize = Vector2(g_screenRect.right, g_screenRect.bottom);
}


void GunSystem::Release()
{
	GameObject::Release();

	RELEASE(m_pShootPoint);
	m_defaultGun.Release();
	m_pCountText->Release();
	delete m_pCountText;
	m_pInfoText->Release();
	delete m_pInfoText;
	RELEASE(m_pRestartBtn)

	delete this;
}


int GunSystem::Start()
{
	//m_pComponentHub->m_pImage->SetImage(g_hasher("BulletCount"));

	m_pCountText->GetComponentHub()->AddComponent(ComponentHub::TEXT);
	RefreshText();

	m_pCountText->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pCountText->GetComponentHub()->m_pGameObject->SetUi(true);
	m_pCountText->GetComponentHub()->m_pTransform->SetPosition(Vector2(100, 40));
	m_pCountText->GetComponentHub()->m_pText->SetColor(D2D1::ColorF(1, 1, 1));

	m_pInfoText->GetComponentHub()->AddComponent(ComponentHub::TEXT);
	m_pInfoText->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pInfoText->GetComponentHub()->m_pGameObject->SetUi(true);
	m_pInfoText->GetComponentHub()->m_pText->SetColor(D2D1::ColorF(1, 1, 1));
	m_pInfoText->GetComponentHub()->m_pText->SetOpacity(0);
	m_pInfoText->GetComponentHub()->m_pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pInfoText->GetComponentHub()->m_pTransform->SetPosition(Vector2(-1150, 800));


	m_pRestartBtn->GetComponentHub()->m_pGameObject->SetUi(true);
	m_pRestartBtn->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pRestartBtn->GetComponentHub()->m_pTransform->SetPosition(Vector2(-650, 300));
	m_pRestartBtn->SetActive(false);

	return 0;
}


int GunSystem::Update()
{
	
	// 화면에 영향을 끼치는 변수들이 행렬에 곱해져있으므로 그것을 상쇄시켜주기 위해 여러 변수들을 곱하고,
	// 화면 좌표를 화면 기준의 데카르트 좌표를 사용하기 위해서 screenSize를 더하고 뺀다.
	m_pComponentHub->m_pTransform->SetPosition(Vector2(
		Camera::GetCameraPos().x + m_screenSize.x * g_screenRatioInv * g_screenMag * 0.5		- 300,
		Camera::GetCameraPos().y - m_screenSize.y * g_screenRatioInv * g_screenMag * 0.5		+ 100
		));

	if (m_shootLock && g_leftDown == false)
		m_shootLock = false;
	if (m_reloadDown)
	{
		m_reloadTime += Time::GetDeltaTime();
		Reload();
	}

	if (Character::m_hp <= 0 && m_infoType != GAME_OVER)
	{
		ShowGameOverText();
	}
	if (m_pRestartBtn->IsClicked())
	{
		GameScene::Reatart = true;
	}
	InfoEndCheck();
	return 0;
}


int GunSystem::OnEvent(Event& event)
{
	GameObject::OnEvent(event);

	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:
		m_screenSize = Vector2(g_screenRect.right, g_screenRect.bottom);
		return 0;
	default:
		break;
	}

	return -1;
}


int GunSystem::Shoot()
{
	if (m_shootLock)
		return -1;


	if (SUCCEEDED(m_pGunPtr->Shoot()))
	{
		m_shootLock = true;
		m_reloadDown = false;
		RefreshText();
		return 0;
	}
	else if (m_infoType != GAME_OVER)
		ShowLackBulletText();

	return -1;
}


int GunSystem::Reload()
{
	if (m_reloadDown == false)
	{
		m_reloadDown = true;
		m_reloadTime = 0;
		return 0;
	}

	if (m_reloadTime < m_pGunPtr->GetReloadDelay())
	{
		return 0;
	}

	if (SUCCEEDED(m_pGunPtr->Reload()))
	{
		RefreshText();
		m_reloadDown = false;
	}
	return -1;
}


void GunSystem::RefreshText()
{
	if (m_pGunPtr->GetRemainBullet() == -1)
		sprintf_s(m_charBuffer, 32, "%d / ∞", m_pGunPtr->GetBullet(), m_pGunPtr->GetRemainBullet());

	else
		sprintf_s(m_charBuffer, 32, "%d / %d", m_pGunPtr->GetBullet(), m_pGunPtr->GetRemainBullet());

	m_pCountText->GetComponentHub()->m_pText->SetText(m_charBuffer);
}


void GunSystem::ChagneGun()
{
	// ---------------------------------> 나중에 로직 구현.
	m_pGunPtr = &m_defaultGun;
	RefreshText();

	m_shootLock = false;
	m_reloadDown = false;
	m_reloadTime = 0;
}


void GunSystem::ShowLackBulletText()
{
	m_infoTextTime = 0;
	m_showInfoText = true;
	m_infoType = LACK_BULLET;
	m_pInfoText->GetComponentHub()->m_pText->SetText("총알이 부족합니다.\nR을 눌러 재장전을 해주세요.");
	m_pInfoText->GetComponentHub()->m_pText->SetOpacity(0);
}


void GunSystem::ShowGameOverText()
{
	m_infoTextTime = 0;
	m_showInfoText = true;
	m_infoType = GAME_OVER;
	m_pInfoText->GetComponentHub()->m_pText->SetText("Game Over");
	m_pInfoText->GetComponentHub()->m_pText->SetOpacity(0);
	m_pRestartBtn->SetActive(true);
	m_pRestartBtn->Start();

}


void GunSystem::InfoEndCheck()
{
	m_infoTextTime += Time::GetDeltaTime();
	switch (m_infoType)
	{
	case GunSystem::NONE:
		return;
	case GunSystem::RELOAD:
		return;
	case GunSystem::LACK_BULLET:
		if (m_infoTextTime > 1)
			m_pInfoText->GetComponentHub()->m_pText->SetOpacity(
				m_pInfoText->GetComponentHub()->m_pText->GetOpacity() - Time::GetDeltaTime()
				);
		else
			m_pInfoText->GetComponentHub()->m_pText->SetOpacity(
				m_pInfoText->GetComponentHub()->m_pText->GetOpacity() + Time::GetDeltaTime()
				);
		return;
	case GunSystem::GAME_OVER:
		m_pInfoText->GetComponentHub()->m_pText->SetOpacity(
			m_pInfoText->GetComponentHub()->m_pText->GetOpacity() + Time::GetDeltaTime() * 0.3
			);
		return;
	}
}