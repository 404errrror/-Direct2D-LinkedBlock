#include "stdafx.h"
#include "DefaultBullet.h"


DefaultBullet::DefaultBullet()
{
}


DefaultBullet::~DefaultBullet()
{
}


void DefaultBullet::Initialize()
{
	GameObject::Initialize();

	m_pComponentHub->AddComponent(ComponentHub::CIRCLE_RENDER);
	m_pComponentHub->m_pCircleRender->SetFill(true);
	m_pComponentHub->m_pTransform->SetScale(Vector2(0.05, 0.05));

}


void DefaultBullet::Release()
{
	GameObject::Release();
}


int DefaultBullet::Start()
{
	return 0;
}


int DefaultBullet::Update()
{

	if (m_pComponentHub->m_pGameObject->isActive() == false)
		return 0;

	m_pComponentHub->m_pCircleRender->SetColor(D2D1::ColorF(
		m_pComponentHub->m_pCircleRender->GetColor().r,
		m_pComponentHub->m_pCircleRender->GetColor().g,
		m_pComponentHub->m_pCircleRender->GetColor().b,
		m_pComponentHub->m_pCircleRender->GetColor().a - Time::GetDeltaTime()
		));

	if (m_pComponentHub->m_pCircleRender->GetColor().a < 0)
	{
		m_pComponentHub->m_pCircleRender->SetColor(D2D1::ColorF(
			m_pComponentHub->m_pCircleRender->GetColor().r,
			m_pComponentHub->m_pCircleRender->GetColor().g,
			m_pComponentHub->m_pCircleRender->GetColor().b,
			1
			));

		m_pComponentHub->m_pGameObject->SetActive(false);
	}

	return 0;
}


int DefaultBullet::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}