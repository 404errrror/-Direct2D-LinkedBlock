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
		if (m_pNowTarget == nullptr)	// ���� Ÿ���� ���ٸ�
		{
			m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;
			return;
		}
		else
		{
			if ((*it)->GetComponentHub()->m_pTransform == m_pNowTarget)		// Ÿ���� ���� �˻��� ������Ʈ�� ���ٸ�
			{
				++it;														// ���� ������Ʈ�� �ٲپ���ϴϱ� �ϳ� ����.
				if (it != MyCharacter::list.end())							// ������Ų ������Ʈ�� ����Ʈ�� ���� �ƴ϶��.
				{
					m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;
					return;
				}
				else														// ������Ų ������Ʈ�� ������ ���̶��
				{
					it = MyCharacter::list.begin();
					m_pNowTarget = (*it)->GetComponentHub()->m_pTransform;				// ó��������Ʈ�� ���ư�����.
					return;
				}
			}
		}
	}


}