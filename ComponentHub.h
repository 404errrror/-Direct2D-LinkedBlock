#pragma once
#include "Component.h"
#include "Image.h"
#include "Transform.h"
#include "FrameAnimation.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Button.h"
#include "RectRender.h"
#include "CircleRender.h"
#include "ShapeAnimation.h"
#include "MotionAnimation.h"
#include "Text.h"

class ComponentHub
{
public:
	enum Type
	{
		TRANSFORM,
		IMAGE,
		FRAME_ANIMATION,
		BOX_COLLIDER,
		RIGIDBODY,
		BUTTON,
		RECT_RENDER,
		CIRCLE_RENDER,
		SHAPE_ANIMATION,
		MOTION_ANIMATION,
		TEXT,
		ALL
	};
	ComponentHub();
	~ComponentHub();

	void Initialzie		(GameObject*);
	void Release		();

	// ���ο� ������Ʈ�� �߰��մϴ�.
	void	AddComponent	(Type);
	// �̺�Ʈ�� ������Ʈ���� �����ϴ�.
	int		SendEvent		(Type, Event&);

public:		// ----------> ��� �׽�Ʈ������ �س���. protected: �� �ٲٱ�. ---> �����غ��� public�� �������Ű���.
	GameObject*			m_pGameObject;
	Image*				m_pImage;
	Transform*			m_pTransform;
	FrameAnimation*		m_pFrameAnimation;
	BoxCollider*		m_pBoxCollider;
	Rigidbody*			m_pRigidbody;
	Button*				m_pButton;
	RectRender*			m_pRectRender;
	CircleRender*		m_pCircleRender;
	ShapeAnimation*		m_pShapeAnimation;
	MotionAnimation*	m_pMotionAnimation;
	Text*		m_pText;
	
};

