#include "stdafx.h"
#include "Button.h"

std::list<Button*> Button::list;

Button::Button()
{
	list.push_back(this);

	m_ImageId = 0;
	m_FocusImageId = 0;
	m_DownImageId = 0;
	m_pImage = nullptr;
	m_pTransform = nullptr;

	m_isDown = m_isUp = m_isEnter = m_isExit = m_isClick = false;
}


Button::~Button()
{
}


void Button::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);

	if (m_pGameObject->GetComponentHub()->m_pImage == nullptr)
		m_pGameObject->GetComponentHub()->AddComponent(ComponentHub::IMAGE);
	if (m_pGameObject->GetComponentHub()->m_pBoxCollider == nullptr)
		m_pGameObject->GetComponentHub()->AddComponent(ComponentHub::BOX_COLLIDER);

	m_pImage = m_pGameObject->GetComponentHub()->m_pImage;
	m_pCollider = m_pGameObject->GetComponentHub()->m_pBoxCollider;
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;

}


void Button::Release()
{
	Component::Release();
	for (std::list<Button*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}


int Button::Start()
{
	m_pCollider->SetTrigger(true);
	return 0;
}


int Button::Update()
{
	if (m_pGameObject->isActive() == false || m_enable == false)
		return 0;

	if (m_pCollider->DetectCollision(g_mouseDesPos))		// 마우스 포인터가 버튼 안에 들어왔으면
	{
		m_isEnter = true;
		if (g_leftDown == false)	// 마우스 안눌럿으면
		{
			if (m_pImage->GetImageId() != m_FocusImageId && m_FocusImageId != NULL)
			{
				m_pImage->SetImage(m_FocusImageId);
				if (m_isDown)
					m_pGameObject->OnEvent(Event(Event::Type::BUTTON_CLICK));
			}
		}
		else						// 마우스 눌렀으면
		{
			if (m_pImage->GetImageId() != m_DownImageId && m_DownImageId != NULL)
			{
				m_isDown = true;
				m_pImage->SetImage(m_DownImageId);
			}
		}

	}
	else			// 마우스 포인터가 밖에 있으면
	{
		m_isEnter = false;
		if (g_leftDown == false)	// 마우스 안눌럿으면
		{
			m_isDown = false;
		}

		if (m_pImage->GetImageId() != m_ImageId)
			m_pImage->SetImage(m_ImageId);
	}
	return 0;
}


int Button::OnEvent(Event& event)
{
	return -1;
}


void Button::SetImage(size_t imageId)
{
	D2D1_RECT_F collRange;
	m_ImageId = imageId;
	m_pImage->SetImage(imageId);

	collRange.right = m_pImage->GetImageWidth() * 0.5 * m_pTransform->GetScale().x;
	collRange.left = collRange.right * -1;
	collRange.top = m_pImage->GetImageHeight() * 0.5 * m_pTransform->GetScale().y;
	collRange.bottom = collRange.top * -1;
	m_pCollider->SetRange(collRange);
}


void Button::SetFucusImage(size_t imageId)
{
	m_FocusImageId = imageId;
}


void Button::SetDownImage(size_t imageId)
{
	m_DownImageId = imageId;
}


void Button::SetScale(Vector2& scale)
{
	D2D1_RECT_F collRange;

	m_pTransform->SetScale(scale);

	collRange.right = m_pImage->GetImageWidth() * 0.5 * m_pTransform->GetScale().x;
	collRange.left = collRange.right * -1;
	collRange.top = m_pImage->GetImageHeight() * 0.5 * m_pTransform->GetScale().y;
	collRange.bottom = collRange.top * -1;
	m_pCollider->SetRange(collRange);
}


bool Button::IsEnter() const
{
	return m_isEnter;
}