#include "stdafx.h"
#include "Light.h"


Light::Light()
{
	m_pCircleRender = nullptr;
	m_minLight = 0;
	m_maxLight = 0;
	m_totalTime = 0;
	m_delayTime = 0;
}


Light::~Light()
{
}


void Light::Initialize()
{
	GameObject::Initialize();
	m_isMask = true;

	m_pComponentHub->AddComponent(ComponentHub::CIRCLE_RENDER);
	m_pCircleRender = m_pComponentHub->m_pCircleRender;
}


void Light::Release()
{
	GameObject::Release();
}


int Light::Start()
{
	m_pComponentHub->m_pCircleRender->SetGraident(true);
	m_pComponentHub->m_pTransform->SetScale(Vector2(10, 10));
	ChageLight(1);
	return 0;
}


int Light::Update()
{
	m_totalTime += Time::GetDeltaTime();

	if (m_totalTime > m_delayTime)
	{
		m_totalTime = 0;
		m_delayTime = CRandom::Range(0.1, 0.5);

		float nowLight = CRandom::Range(m_minLight, m_maxLight);

		m_pCircleRender->SetColor(D2D1::ColorF(
			m_pCircleRender->GetColor().r,
			m_pCircleRender->GetColor().g,
			m_pCircleRender->GetColor().b,
			nowLight
			));
		m_pComponentHub->m_pTransform->SetScale(Vector2(nowLight * 10, nowLight * 10));
	}

	if (Character::m_hp <= 0)
	{
		ChageLight(m_nowStrength - Time::GetDeltaTime() * 0.5);
	}

	return 0;
}


int Light::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void Light::ChageLight(float strength)
{
	if (strength < 0)
		strength = 0;
	m_nowStrength = strength;
	m_minLight = strength * 0.9;
	m_maxLight = strength * 1.1;
}