#include "stdafx.h"
#include "Character.h"

int Character::m_hp = 100;

Character::Character()
{
	m_pHpText = nullptr;
	m_screenSize = Vector2(g_screenRect.right, g_screenRect.bottom);
}


Character::~Character()
{
}


void Character::Initialize()
{
	GameObject::Initialize();
	SetId("Character");
	m_pComponentHub->AddComponent(ComponentHub::IMAGE);
	m_pComponentHub->m_pImage->SetImage(g_hasher("Character"));

	m_pHpText = new GameObject();
	m_pHpText->Initialize();
	m_pHpText->GetComponentHub()->AddComponent(ComponentHub::TEXT);
	m_pHpText->GetComponentHub()->m_pText->SetColor(D2D1::ColorF(1, 0.3, 0.3));
	m_pHpText->SetUi(true);


}


void Character::Release()
{
	GameObject::Release();
	m_pHpText->Release();
	delete m_pHpText;
	delete this;
}


int Character::Start()
{
	m_pComponentHub->m_pImage->SetBottom(-75);
	return 0;
}


int Character::Update()
{

	if (m_hp < 0)
		m_hp = 0;

	char temp[16];
	sprintf_s(temp,"Hp : %d", m_hp);
	m_pHpText->GetComponentHub()->m_pTransform->SetPosition(Vector2(
		Camera::GetCameraPos().x + m_screenSize.x * g_screenRatioInv * g_screenMag * 0.5 - 300,
		Camera::GetCameraPos().y - m_screenSize.y * g_screenRatioInv * g_screenMag * 0.5 + 1000
		));
	m_pHpText->GetComponentHub()->m_pText->SetText(temp);

	return 0;
}


int Character::OnEvent(Event& event)
{
	GameObject::OnEvent(event);

	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:
		m_screenSize = Vector2(g_screenRect.right, g_screenRect.bottom);
		return 0;
	default:
		return -1;
	}

}