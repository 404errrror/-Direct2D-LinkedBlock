#include "stdafx.h"
#include "MotionAnimation.h"

std::list<MotionAnimation*> MotionAnimation::list;

MotionAnimation::MotionAnimation()
{
	list.push_back(this);

	m_pTransform = nullptr;
	m_time = 1;
	m_totalTime = 0;
	m_isPlay = false;
	m_startPos = Vector2(0, 0);
	m_endPos = Vector2(0, 0);
	m_type = MOTION_ANIMATION_DEAULT;

	m_smoothEndSpeed = 1;
}


MotionAnimation::~MotionAnimation()
{
}



void  MotionAnimation::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;
}


void MotionAnimation::Release()
{
	Component::Release();
	for (std::list<MotionAnimation*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}

	delete this;
}


int MotionAnimation::Start()
{
	return 0;
}


int MotionAnimation::Update()
{
	if (m_pGameObject->isActive() == false || m_enable == false)
		return 0;

	if (m_isPlay)
	{
		switch (m_type)
		{
		case MotionAnimation::MOTION_ANIMATION_DEAULT:			Move();				break;
		case MotionAnimation::MOTION_ANIMATION_SMOOTH_START:	SmoothMoveStart();	break;
		case MotionAnimation::MOTION_ANIMATION_SMOOTH_END:		SmoothMoveEnd();	break;
		case MotionAnimation::MOTION_ANIMATION_SMOOTH:			SmoothMove();		break;
		default:
			break;
		}
	}

	return 0;
}


int MotionAnimation::OnEvent(Event& event)
{
	return -1;
}


void MotionAnimation::SetTime(float time)
{
	m_time = time;
}


void MotionAnimation::SetMove(Vector2 startPos, Vector2 endPos)
{
	m_startPos = startPos;
	m_endPos = endPos;
}


void MotionAnimation::SetMove(Vector2 endPos)
{
	m_startPos = m_pTransform->GetPosition();
	m_endPos = endPos;
}


void MotionAnimation::SetType(Type type)
{
	m_type = type;
}


void MotionAnimation::Move()
{
	m_totalTime += Time::GetDeltaTime();
	// 애니메이션 마지막 프레임일때
	if (m_totalTime > m_time)
	{
		m_pTransform->Translate(
			(m_endPos - m_startPos) * ((m_totalTime - m_time) / m_time)
			);

		m_isPlay = false;
	}
	else
		m_pTransform->Translate(
			(m_endPos - m_startPos) * (Time::GetDeltaTime() / m_time)
			);
}


void MotionAnimation::SmoothMoveStart()
{
	Vector2 distance = m_endPos - m_startPos;
	// 누적된 거리(?)로 나오기 때문에 계산한 거리에 전의 거리를 빼야한다.
	Vector2 beforeMoveDistance = distance * (m_totalTime * m_totalTime / (m_time * m_time));

	m_totalTime += Time::GetDeltaTime();


	if (m_totalTime > m_time)
	{
		m_pTransform->Translate(
			distance * (m_totalTime * m_totalTime / (m_time * m_time)) - beforeMoveDistance
			);
		m_isPlay = false;
	}
	else
	{

		m_pTransform->Translate(
			distance * (m_totalTime * m_totalTime / (m_time * m_time)) - beforeMoveDistance
			);
	}

	// y = x^2
}


void MotionAnimation::SmoothMoveEnd()
{
	Vector2 myDistance = m_endPos - m_pTransform->GetPosition();

	Vector2 distance = m_endPos - m_startPos;
	Vector2 beforeMoveDistance = distance * sqrt(m_totalTime / m_time);

	m_totalTime += Time::GetDeltaTime();

	if (m_totalTime > m_time)
	{
		m_pTransform->Translate(
			distance * sqrt(m_totalTime / m_time) - beforeMoveDistance
			);
		m_isPlay = false;
	}
	else
	{

		m_pTransform->Translate(
			distance * sqrt(m_totalTime / m_time) - beforeMoveDistance
			);
	}

	// y = 루트x
}


void MotionAnimation::SmoothMove()
{
	float distance = Vector2::GetDistance(m_startPos, m_endPos);
	Vector2 subPos = m_endPos - m_startPos;
	//if (distance * 0.5 < Vector2::GetDistance(m_pTransform->GetPosition(), m_endPos))
	//{
	//	SmoothMoveStart();
	//}
	//else
	//{
	//	SmoothMoveEnd();
	//}

	float halfTime = m_time * 0.5;

	if (m_totalTime < halfTime)
	{
		Vector2 beforeMoveDistance = subPos * (m_totalTime * m_totalTime / (halfTime * halfTime));

		m_totalTime += Time::GetDeltaTime();



		if (m_totalTime >= halfTime)
		{
			m_pTransform->SetPosition(
				m_startPos + subPos * 0.5
				);
			m_totalTime = halfTime;
			m_tEndTime = m_totalTime;
			m_tStartPos = m_pTransform->GetPosition();
			return;
		//	m_isPlay = false;
		}
		else
		{

			m_pTransform->SetPosition(
				m_startPos + (subPos * (m_totalTime * m_totalTime / (halfTime * halfTime))) * 0.5
				);
		}

	}
	else // 솔직히 이 밑부분 왜 작동되는지 잘 모르겟음. 시간없으니깐 다음에.
	{
		Vector2 beforeMoveDistance = subPos * sqrt(m_totalTime / halfTime);
		m_totalTime += Time::GetDeltaTime();


		if (m_totalTime > m_time)
		{
			m_pTransform->Translate(
				(subPos * sqrt(m_totalTime/ halfTime) - beforeMoveDistance) * 1.2 * m_smoothEndSpeed
				);
			m_isPlay = false;
		}
		else
		{

			m_pTransform->Translate(
				(subPos * sqrt(m_totalTime / halfTime) - beforeMoveDistance)* 1.2 * m_smoothEndSpeed
				);;
		}
	}

//	float halfTime = m_time * 0.5;

	//if (m_tEndTime == 0)
	//{
	//	Vector2 beforeMoveDistance = subPos * (m_totalTime * m_totalTime / (halfTime * halfTime)) * 0.5;

	//	m_totalTime += Time::GetDeltaTime();


	//	if (m_totalTime >= halfTime)
	//	{
	//		m_pTransform->Translate(
	//			subPos * (halfTime - m_totalTime)
	//			);
	//		m_tEndTime = m_time / 2;
	//		m_totalTime = 0;
	//		m_tStartPos = m_pTransform->GetPosition();
	//		return;
	//	}
	//	else
	//	{

	//		m_pTransform->Translate(
	//			subPos * (m_totalTime * m_totalTime / (halfTime * halfTime)) * 0.5 - beforeMoveDistance
	//			);
	//	}

	//}
	//else
	//{
	//	subPos = (m_endPos - m_tStartPos);
	//	Vector2 beforeMoveDistance = subPos * sqrt(m_totalTime / halfTime);

	//	m_totalTime += Time::GetDeltaTime();


	//	if (m_totalTime > halfTime)
	//	{

	//		m_pTransform->Translate(
	//			(subPos * (halfTime - m_totalTime))
	//			);
	//		m_isPlay = false;
	//	}
	//	else
	//	{

	//		m_pTransform->Translate(
	//			(subPos * sqrt(m_totalTime / halfTime) - beforeMoveDistance)
	//			);;
	//	}
	//}

}


bool MotionAnimation::IsPlay()
{
	return m_isPlay;
}


void MotionAnimation::Play()
{
	m_isPlay = true;
	m_totalTime = 0;
	m_pTransform->SetPosition(m_startPos);

	if (m_type == MOTION_ANIMATION_SMOOTH)
	{
		m_tEndTime = 0;
	}
}


void MotionAnimation::Stop()
{
	m_isPlay = false;
}