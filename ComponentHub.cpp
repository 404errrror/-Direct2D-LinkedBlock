#include "stdafx.h"
#include "ComponentHub.h"

ComponentHub::ComponentHub()
{
	m_pGameObject = nullptr;
	m_pImage = nullptr;
	m_pTransform = nullptr;
	m_pFrameAnimation = nullptr;
	m_pBoxCollider = nullptr;
	m_pRigidbody = nullptr;
	m_pButton = nullptr;
	m_pRectRender = nullptr;
	m_pCircleRender = nullptr;
	m_pShapeAnimation = nullptr;
	m_pMotionAnimation = nullptr;
	m_pText = nullptr;
}


ComponentHub::~ComponentHub()
{
}


void ComponentHub::Initialzie(GameObject* gameObject)
{
	m_pGameObject = gameObject;
}


void ComponentHub::Release()
{
	RELEASE(m_pImage);
	RELEASE(m_pTransform);
	RELEASE(m_pFrameAnimation);
	RELEASE(m_pBoxCollider);
	RELEASE(m_pRigidbody);
	RELEASE(m_pButton);
	RELEASE(m_pRectRender);
	RELEASE(m_pCircleRender);
	RELEASE(m_pMotionAnimation);
	RELEASE(m_pShapeAnimation);
	RELEASE(m_pText);
	delete this;
}


void ComponentHub::AddComponent(Type componentType)
{
	switch (componentType)
	{
	case TRANSFORM:
		m_pTransform = new Transform;
		m_pTransform->Initialize(m_pGameObject);
		return;

	case IMAGE:
		///////////// -----------------> 이미 할당되있을때 해야할 코드 추가하기.
		m_pImage = new Image;
		m_pImage->Initialize(m_pGameObject);
		return;

	case FRAME_ANIMATION:
		m_pFrameAnimation = new FrameAnimation;
		m_pFrameAnimation->Initialize(m_pGameObject);
		return;

	case BOX_COLLIDER:
		m_pBoxCollider = new BoxCollider;
		m_pBoxCollider->Initialize(m_pGameObject);
		return;

	case RIGIDBODY:
		m_pRigidbody = new Rigidbody;
		m_pRigidbody->Initialize(m_pGameObject);
		return;

	case BUTTON:
		m_pButton = new Button;
		m_pButton->Initialize(m_pGameObject);
		return;

	case RECT_RENDER:
		m_pRectRender = new RectRender;
		m_pRectRender->Initialize(m_pGameObject);
		return;

	case CIRCLE_RENDER:
		m_pCircleRender = new CircleRender;
		m_pCircleRender->Initialize(m_pGameObject);
		return;

	case SHAPE_ANIMATION:
		m_pShapeAnimation = new ShapeAnimation;
		m_pShapeAnimation->Initialize(m_pGameObject);
		return;

	case MOTION_ANIMATION:
		m_pMotionAnimation = new MotionAnimation;
		m_pMotionAnimation->Initialize(m_pGameObject);
		return;

	case TEXT:
		m_pText = new Text;
		m_pText->Initialize(m_pGameObject);
		return;
	default:
		break;
	}
}


int ComponentHub::SendEvent(Type componentType, Event& event)
{
	switch (componentType)
	{
	case ComponentHub::TRANSFORM:
		if (m_pTransform)
		{
			m_pTransform->OnEvent(event);
			return 0;
		}
		else
			return -1;

	case ComponentHub::IMAGE:
		if (m_pImage)
		{
			m_pImage->OnEvent(event);
			return 0;
		}
		else
			return -1;

	case ComponentHub::RECT_RENDER:
		if (m_pRectRender)
		{
			m_pRectRender->OnEvent(event);
			return 0;
		}
		else
			return -1;

	case ComponentHub::CIRCLE_RENDER:
		if (m_pCircleRender)
		{
			m_pCircleRender->OnEvent(event);
			return 0;
		}
		else
			return -1;

	case ComponentHub::TEXT:
		if (m_pText)
		{
			m_pText->OnEvent(event);
			return 0;
		}
		else return -1;

	case ComponentHub::ALL:
		SendEvent(TRANSFORM, event);
		SendEvent(IMAGE, event);
		SendEvent(RECT_RENDER, event);
		SendEvent(CIRCLE_RENDER, event);
		SendEvent(TEXT, event);
		return 0;
	default:
		break;
	}
}