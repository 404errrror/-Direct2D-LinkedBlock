#include "stdafx.h"
#include "ShapeAnimation.h"

std::list<ShapeAnimation*> ShapeAnimation::list;

ShapeAnimation::ShapeAnimation()
{
	list.push_back(this);
	m_pTransform = nullptr;
	m_animationType = ANIMATION_DEFAULT;
	m_startScale = m_endScale = Vector2(0, 0);
	m_time = 1;
	m_totalTime = 0;
}


ShapeAnimation::~ShapeAnimation()
{
}


void ShapeAnimation::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;
}


void ShapeAnimation::Release()
{
	Component::Release();
	for (std::list<ShapeAnimation*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}


int ShapeAnimation::Start()
{
	return 0;
}


int ShapeAnimation::Update()
{
	if (m_pGameObject->isActive() == false || m_enable == false)
		return 0;

	if (m_isPlay)
	{
		switch (m_animationType)
		{
		case ShapeAnimation::ANIMATION_DEFAULT:			Default();		break;
		case ShapeAnimation::ANIMATION_SMOOTH_START:	SmoothStart();	break;
		case ShapeAnimation::ANIMATION_SMOOTH_END:		SmoothEnd();	break;
		}
	}

	return 0;
}


int ShapeAnimation::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	default:
		return -1;
	}
}


void ShapeAnimation::SetAnimationType(AnimationType type)
{
	m_animationType = type;
}


void ShapeAnimation::SetTime(float time)
{
	m_time = time;
}


void ShapeAnimation::SetScale(Vector2 startScale, Vector2 endScale)
{
	m_startScale = startScale;
	m_endScale = endScale;
}


void ShapeAnimation::SetScale(Vector2 endScale)
{
	m_startScale = m_pTransform->GetScale();
	m_endScale = endScale;
}

//
//void ShapeAnimation::SetStartScale(Vector2 scale)
//{
//	m_startScale = scale;
//}
//
//
//void ShapeAnimation::SetEndScale(Vector2 scale)
//{
//	m_endScale = scale;
//}


bool ShapeAnimation::IsPlay()
{
	return m_isPlay;
}


void ShapeAnimation::Play()
{
	m_isPlay = true;
	m_totalTime = 0;
	m_pTransform->SetScale(m_startScale);
}


void ShapeAnimation::Stop()
{
	m_isPlay = false;
}


void ShapeAnimation::Default()
{

	m_totalTime += Time::GetDeltaTime();
	Vector2 subScale = m_endScale - m_startScale;

	if (m_totalTime > m_time)
	{
		m_pTransform->SetScale(
			m_startScale + subScale
			);
		Stop();
	}
	else
	{
		m_pTransform->SetScale(
			m_startScale + subScale * (m_totalTime / m_time)
			);
	}

}


void ShapeAnimation::SmoothStart()
{
	m_totalTime += Time::GetDeltaTime();
	Vector2 subScale = m_endScale - m_startScale;
	float x = m_totalTime / m_time;

	if (m_totalTime > m_time)
	{
		m_pTransform->SetScale(
			m_startScale + subScale
			);
		Stop();
	}
	else
	{
		m_pTransform->SetScale(
		//	m_startScale + subScale * (m_totalTime * m_totalTime / (m_time * m_time))
		m_startScale + subScale *(-sqrt(1 - x * x) + 1)
			);
	}
}


void ShapeAnimation::SmoothEnd()
{
	m_totalTime += Time::GetDeltaTime();
	Vector2 subScale = m_endScale - m_startScale;
	float x = m_totalTime / m_time;

	if (m_totalTime > m_time)
	{
		m_pTransform->SetScale(
			m_startScale + subScale
			);
		Stop();
	}
	else
	{
		m_pTransform->SetScale(
		//	m_startScale + subScale * sqrt(m_totalTime/ m_time)
			m_startScale + subScale * sqrt(1 - (x - 1) * (x - 1))
			);
	}
}