#include "stdafx.h"
#include "CircleEffect.h"


CircleEffect::CircleEffect()
{
	m_type = TYPE_NONE;
	m_startScale = Vector2(0, 0);
	m_endScale = Vector2(0, 0);
	m_isPlay = false;
	m_color = D2D1::ColorF(0, 0, 0);
	m_time = 1;
}


CircleEffect::~CircleEffect()
{
}


void CircleEffect::Initialize()
{
	GameObject::Initialize();

	SetId("CircleEffect");
	m_pComponentHub->AddComponent(ComponentHub::CIRCLE_RENDER);
	m_pComponentHub->AddComponent(ComponentHub::SHAPE_ANIMATION);
}


void CircleEffect::Release()
{
	GameObject::Release();
	delete this;
}


int CircleEffect::Start()
{
	return 0;
}


int CircleEffect::Update()
{

	return 0;
}


void CircleEffect::SetType(Type type)
{
	m_type = type;
}


void CircleEffect::SetScale(Vector2 endScale)
{
	m_endScale = endScale;
}


void CircleEffect::SetScale(Vector2 startScale, Vector2 endScale)
{
	m_startScale = startScale;
	m_endScale = endScale;
}


void CircleEffect::SetColor(D2D1_COLOR_F color)
{
	m_color = color;
}


void CircleEffect::SetTime(float time)
{
	m_time = time;
}


void CircleEffect::Play()
{

	m_pComponentHub->m_pShapeAnimation->SetScale(m_startScale, m_endScale);
	switch (m_type)
	{
	case CircleEffect::TYPE_NONE:
		m_pComponentHub->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_DEFAULT);
		m_pComponentHub->m_pCircleRender->SetColor(m_color);
		break;
	case CircleEffect::TYPE_MASK:
		m_pComponentHub->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);
		m_pComponentHub->m_pShapeAnimation->SetTime(m_time);
		m_pComponentHub->m_pCircleRender->SetColor(D2D1::ColorF(0, 0, 0, 1));
		m_pComponentHub->m_pCircleRender->SetFill(true);
		SetMask(true);
		break;
	default:
		break;
	}

	m_pComponentHub->m_pShapeAnimation->Play();
}


bool CircleEffect::IsPlay()
{
	return m_pComponentHub->m_pShapeAnimation->IsPlay();
}


void CircleEffect::Stop()
{
	m_pComponentHub->m_pShapeAnimation->Stop();
}