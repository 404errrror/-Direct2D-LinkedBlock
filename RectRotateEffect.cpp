#include "stdafx.h"
#include "RectRotateEffect.h"
#include <conio.h>

RectRotateEffect::RectRotateEffect()
{
	m_pTransform = nullptr;
	m_baseColor = D2D1::ColorF(D2D1::ColorF::Black);
	m_rectArr = nullptr;
	m_colorArr = nullptr;
	m_isFadeOut = false;
	m_fadeOutSpeed = 0;
	m_amount = 0;
	m_totalTime = 0;
}


RectRotateEffect::~RectRotateEffect()
{
}


void RectRotateEffect::Initialize()
{
	GameObject::Initialize();
	m_pTransform = m_pComponentHub->m_pTransform;
}


void RectRotateEffect::Release()
{
	GameObject::Release();

	for (int i = 0; i < m_amount; ++i)
		m_rectArr[i].Release();

	delete[] m_rectArr;

	delete[] m_colorArr;
	
	delete this;
}


int RectRotateEffect::Start()
{
	return 0;
}


int RectRotateEffect::Update()
{
	if (m_active == false)
		return 0;

	if (m_type == TYPE_FADEOUT || m_type == TYPE_FADEOUT_MANY)
		FadeOutEffect();
	if (m_type == TYPE_DEFAULT)
		DefaultEffect();

	

	// FadeOutEffect
	if (m_isFadeOut)
	{
		for (int i = 0; i < m_amount; ++i)
		{
			m_colorArr[i].a -= Time::GetDeltaTime() * m_fadeOutSpeed;
			m_rectArr[i].GetComponentHub()->m_pRectRender->SetColor(m_colorArr[i]);
		}
	}
	return 0;
}


int RectRotateEffect::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	return -1;
}


void RectRotateEffect::SetType(EffectType effectType)
{
	m_type = effectType;
	switch (effectType)
	{

	case RectRotateEffect::TYPE_FADEOUT:
		m_amount = 3;
		m_defaultSpeed = 5;
		break;
	case RectRotateEffect::TYPE_FADEOUT_MANY:
		m_amount = 4;
		m_defaultSpeed = 5;
		break;
	case RectRotateEffect::TYPE_DEFAULT:
		m_amount = 3;
		m_defaultSpeed = 5;
		break;
	default:
		return;
	}

	m_rectArr = new GameObject[m_amount];
	m_colorArr = new D2D1_COLOR_F[m_amount];
	for (int i = 0; i < m_amount; ++i)
	{
		m_rectArr[i].Initialize();
		m_rectArr[i].GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);
		m_rectArr[i].GetComponentHub()->m_pRectRender->Start();
		m_rectArr[i].GetComponentHub()->m_pTransform->SetParent(m_pTransform);
		m_rectArr[i].GetComponentHub()->m_pTransform->SetScale(Vector2(0.7, 0.7));
		m_rectArr[i].GetComponentHub()->m_pRectRender->Refresh();
		m_rectArr[i].GetComponentHub()->m_pRectRender->SetColor(m_baseColor);
		m_rectArr[i].GetComponentHub()->m_pRectRender->SetStrokeWidth(3);

		m_colorArr[i] = m_rectArr[i].GetComponentHub()->m_pRectRender->GetColor();
	}



	switch (effectType)
	{
	case RectRotateEffect::TYPE_FADEOUT:
	case RectRotateEffect::TYPE_FADEOUT_MANY:
		for (int i = 1; i < m_amount; ++i)
			m_rectArr[i].SetActive(false);
		break;
	default:
		break;
	}

}


void RectRotateEffect::SetColor(D2D1_COLOR_F color)
{
	m_baseColor = color;
	for (int i = 0; i < m_amount; ++i)
		m_rectArr[i].GetComponentHub()->m_pRectRender->SetColor(m_baseColor);
}


void RectRotateEffect::FadeOut(float fadeOutSpeed)
{
	m_isFadeOut = true;
	m_fadeOutSpeed = fadeOutSpeed;
}


void RectRotateEffect::FadeOutEffect()
{
	m_rectArr[0].GetComponentHub()->m_pTransform->Rotate(m_defaultSpeed * 20 * Time::GetDeltaTime());

	m_totalTime += Time::GetDeltaTime();
	for (int i = 1; i < m_amount; ++i)
	{
		if (m_rectArr[i].isActive() == false)
		{
			if (m_totalTime > 1.1)
			{
				m_totalTime = 0;
				m_colorArr[i] = m_rectArr[0].GetComponentHub()->m_pRectRender->GetColor();
				m_rectArr[i].GetComponentHub()->m_pTransform->SetRotation(
					m_rectArr[0].GetComponentHub()->m_pTransform->GetRotation()
					);
				m_rectArr[i].SetActive(true);
			}
		}
		else // m_rectArr[i].isActive() == true
		{

			if (m_colorArr[i].a < 0)
				m_rectArr[i].SetActive(false);
			// --------------> brush가 아니라 color_f로 꼭 바꾸기
			m_colorArr[i].a -= Time::GetDeltaTime() * m_defaultSpeed * 0.1;
			m_rectArr[i].GetComponentHub()->m_pRectRender->SetColor(m_colorArr[i]);
		}
	}
}


void RectRotateEffect::DefaultEffect()
{
	for (int i = 0; i < m_amount; ++i)
	{
		m_rectArr[i].GetComponentHub()->m_pTransform->Rotate(m_defaultSpeed * 10 * Time::GetDeltaTime() * (i + 1));
	}
}