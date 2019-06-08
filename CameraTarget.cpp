#include "stdafx.h"
#include "CameraTarget.h"


CameraTarget::CameraTarget()
{
	m_pNowTarget = nullptr;
	mouseSencivity = 0.4;
	m_keyDelay = 0;
}


CameraTarget::~CameraTarget()
{
}


void CameraTarget::Initialize()
{
	GameObject::Initialize();
	SetId("CameraTarget");
	m_pTransform = m_pComponentHub->m_pTransform;
}


void CameraTarget::Release()
{
	GameObject::Release();
	Camera::SetObject(nullptr);
	delete this;
}


int CameraTarget::Start()
{
	Camera::SetObject(m_pTransform);
	return 0;
}


int CameraTarget::Update()
{
	if (m_active == false)
		return 0;
	Vector2 averPosition;
	Vector2 mousePos = Vector2(
		g_mouseDesPos.GetScreenVector().x * g_screenRatio - g_screenRect.right * 0.5,
		g_mouseDesPos.GetScreenVector().y * g_screenRatio * -1 + g_screenRect.bottom * 0.5
		);
	m_keyDelay += Time::GetDeltaTime();

	if (m_pNowTarget != nullptr)
	{
		Vector2 temp = m_pNowTarget->GetPosition();
		averPosition = temp + mousePos * mouseSencivity;
	}
	else
	{

		averPosition = (Vector2(
			0 + mousePos.x, 0 + mousePos.y
			)) * mouseSencivity;
	}

	m_pTransform->SetPosition(averPosition);
	return 0;
}


int CameraTarget::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void CameraTarget::RefreshTarget()
{
	for (std::list<MyCharacter*>::iterator it = MyCharacter::list.begin(); it != MyCharacter::list.end(); ++it)
	{
		m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;
		Camera::SetObject(m_pNowTarget);
		break;
	}
}


void CameraTarget::ChangeNextTarget()
{
	if (m_keyDelay < 0.3)
		return;
	m_keyDelay = 0;
	for (std::list<MyCharacter*>::iterator it = MyCharacter::list.begin(); it != MyCharacter::list.end(); ++it)
	{
		if (m_pNowTarget == nullptr)	// 만약 타겟이 없다면
		{
			m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;
			return;
		}
		else
		{
			if ((*it)->GetComponentHub()->m_pTransform == m_pNowTarget)		// 타겟이 지금 검색한 오브젝트와 같다면
			{
				++it;														// 다음 오브젝트로 바꾸어야하니깐 하나 증감.
				if (it != MyCharacter::list.end())							// 증감시킨 오브젝트가 리스트의 끝이 아니라면.
				{
					m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;
					return;
				}
				else														// 증감시킨 오브젝트가 파일의 끝이라면
				{
					it = MyCharacter::list.begin();
					m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;				// 처음오브젝트로 돌아가야함.
					return;
				}
			}
		}
	}


}