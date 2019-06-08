#include "stdafx.h"
#include "PotalEffect.h"

// -------------------> RectScaleEffect로 클래스명 바꾸기
PotalEffect::PotalEffect()
{
	m_pTransform = nullptr;
	m_effectArr = nullptr;
	m_baseColor = D2D1::ColorF(D2D1::ColorF::Black);
	m_baseColor.a = 0;
	m_amount = 0;
	m_speed = 1;
	m_totalTime = 0;
	m_fadeIn = false;
	m_startScale = Vector2(1, 1);
	m_endScale = Vector2(0, 0);
	m_isPlay = false;
}


PotalEffect::~PotalEffect()
{
}


void PotalEffect::Initialize()
{
	GameObject::Initialize();
	SetId("PotalEffect");
}


void PotalEffect::Release()
{
	GameObject::Release();

	for (int i = 0; i < m_amount; i++)
	{
		m_effectArr[i].Release();
	}
	delete[] m_effectArr;
	delete[] m_colorArr;

	delete this;
}


int PotalEffect::Start()
{
	m_pTransform = m_pComponentHub->m_pTransform;
	return 0;
}


int PotalEffect::Update()
{
	m_totalTime += Time::GetDeltaTime();
	for (int i = 0; i < m_amount; ++i)
	{
		if (m_effectArr[i].isActive())
		{

			if (m_fadeIn == false && m_colorArr[i].a < 0)
			{
				m_effectArr[i].SetActive(false);
				continue;
			}
			else if (m_fadeIn == true && m_colorArr[i].a > 1)
			{
				m_effectArr[i].SetActive(false);
				continue;
			}
			m_effectArr[i].GetComponentHub()->m_pRectRender->SetColor(m_colorArr[i]);

			if (m_fadeIn)
			{
				m_colorArr[i].a += Time::GetDeltaTime() * m_speed;
			}
			else
			{
				m_colorArr[i].a -= Time::GetDeltaTime() * m_speed;
			}
		}
		else if (m_totalTime > 1 / m_speed / m_amount)
		{
			if (m_isPlay == false)
				continue;
			m_colorArr[i] = m_baseColor;
			m_effectArr[i].GetComponentHub()->m_pTransform->SetScale(m_startScale);
			m_effectArr[i].GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(m_colorArr[i].r, m_colorArr[i].g, m_colorArr[i].b, 0));
			m_effectArr[i].GetComponentHub()->m_pShapeAnimation->Play();
			m_effectArr[i].SetActive(true);
			m_totalTime = 0;
		}
	}
	return 0;
}


int PotalEffect::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void PotalEffect::SetEffectAmout(int amount)
{
	m_amount = amount;

	m_effectArr = new GameObject[m_amount];
	m_colorArr = new D2D1_COLOR_F[m_amount];

	for (int i = 0; i < m_amount; ++i)
	{
		m_effectArr[i].Initialize();
		m_effectArr[i].SetId("PotalEffectChild");
		m_effectArr[i].GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
		m_effectArr[i].GetComponentHub()->m_pTransform->SetScale(m_startScale);

		m_effectArr[i].GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);
		m_effectArr[i].GetComponentHub()->AddComponent(ComponentHub::SHAPE_ANIMATION);
		m_effectArr[i].GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		m_effectArr[i].GetComponentHub()->m_pRectRender->SetStrokeWidth(2);
		m_effectArr[i].GetComponentHub()->m_pShapeAnimation->SetScale(m_endScale);
		m_effectArr[i].GetComponentHub()->m_pShapeAnimation->SetTime(1 / m_speed);
		m_effectArr[i].GetComponentHub()->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);
		m_effectArr[i].SetActive(false);

		m_colorArr[i] = m_baseColor;
	}
}


void PotalEffect::SetColor(D2D1_COLOR_F color)
{
	m_baseColor = color;
	if (m_fadeIn)
		m_baseColor.a = 0;
	else
		m_baseColor.a = 1;
}


void PotalEffect::SetSpeed(float speed, float alphaSpeed)
{
	m_speed = speed;
	if (alphaSpeed == 0)
		m_alphaSpeed = 1;
	else
		m_alphaSpeed = alphaSpeed;
}


void PotalEffect::SetFade(bool fade)
{
	m_fadeIn = fade;

	if (m_fadeIn)
		m_baseColor.a = 0;
	else
		m_baseColor.a = 1;
}


void PotalEffect::SetScale(Vector2 start, Vector2 end)
{
	m_startScale = start;
	m_endScale = end;
	for (int i = 0; i < m_amount; ++i)
	{
		m_effectArr[i].GetComponentHub()->m_pTransform->SetScale(m_startScale);
		m_effectArr[i].GetComponentHub()->m_pShapeAnimation->SetScale(m_endScale);
	}
}


void PotalEffect::SetAnimationType(ShapeAnimation::AnimationType type)
{
	for (int i = 0; i < m_amount; ++i)
		m_effectArr[i].GetComponentHub()->m_pShapeAnimation->SetAnimationType(type);
}


void PotalEffect::Play()
{
	m_isPlay = true;
}


bool PotalEffect::IsPlay()
{
	return m_isPlay;

}


void PotalEffect::Stop()
{
	m_isPlay = false;
}