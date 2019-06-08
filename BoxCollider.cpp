#include "stdafx.h"
#include "BoxCollider.h"
#include "D2DClass.h"

std::list<BoxCollider*> BoxCollider::list;

BoxCollider::BoxCollider()
{

	left = top = right = bottom = 0;
	center = { 0, 0 };
	m_pTransfrom = nullptr;
	isTrigger = false;
	list.push_back(this);
}


BoxCollider::~BoxCollider()
{
}


void BoxCollider::Initialize(GameObject* gameObject)
{
	Component::Initialize(gameObject);
	m_pTransfrom = m_pGameObject->GetComponentHub()->m_pTransform;
}


void BoxCollider::Release()
{
	Component::Release();
	for (std::list<BoxCollider*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}


int BoxCollider::Start()
{
	if (
		m_pGameObject->GetComponentHub()->m_pImage != nullptr &&
		left == 0 && top == 0 && right == 0 && bottom == 0
		)
	{
		right = m_pGameObject->GetComponentHub()->m_pImage->GetImageWidth() * 0.5 * m_pTransfrom->GetScale().x;
		left = right * -1;
		top = m_pGameObject->GetComponentHub()->m_pImage->GetImageWidth() * 0.5 * m_pTransfrom->GetScale().y;
		bottom = top * -1;
	}
	// 뒤집히면 충돌 체크가 안됨.
	if (top < bottom)
	{
		float temp = top;
		top = bottom;
		bottom = temp;
	}

	if (right < left)
	{
		float temp = right;
		right = left;
		left = temp;
	}

	return 0;
}


int BoxCollider::Update()
{
	if (m_pGameObject->isActive() == false || m_enable == false)
	{
		left = top = right = bottom = 0;
		return 0;
	}

	center = m_pTransfrom->GetPosition(right * 2, top * 2);
	Camera::Apply(center);
	if (g_debugMode)
		Debug();

	return 0;
}


void BoxCollider::Debug()
{
	ID2D1BitmapRenderTarget* bitmapRender = GameObject::GetRenderTarget();
	D2D1_POINT_2F screenVector = center.GetScreenVector();


	bitmapRender->DrawRectangle(
		D2D1::RectF(
		screenVector.x + left,
		screenVector.y + top,
		screenVector.x + right,
		screenVector.y + bottom),
		D2DClass::GetSolidBrush(D2D1::ColorF(0, 1, 0))
		);


}


int BoxCollider::OnEvent(Event& event)
{
	if(FAILED(m_pGameObject->OnEvent(event)))
		return -1;

}


void BoxCollider::SetRange(D2D1_RECT_F detectRect)
{
	left = detectRect.left;
	right = detectRect.right;
	top = detectRect.top;
	bottom = detectRect.bottom;


}


void BoxCollider::SetRange(float width, float height)
{
	// 데카르트 좌표계

	left =		width * -0.5;
	right =		width * 0.5;
	top =		height * 0.5;
	bottom =	height * -0.5;
}


void BoxCollider::SetTrigger(bool isTrigger)
{
	this->isTrigger = isTrigger;
}


D2D1_RECT_F BoxCollider::GetRange() const
{

	return D2D1::RectF(center.x + left, center.y + top, center.x + right, center.y + bottom);
}


float BoxCollider::GetMass() const
{
	if (m_pGameObject->GetComponentHub()->m_pRigidbody)
		return m_pGameObject->GetComponentHub()->m_pRigidbody->GetMass();
	else
		return -1;
}


bool BoxCollider::IsTrigger() const
{
	if (isTrigger)
		return true;
	else
		return false;
}


bool BoxCollider::DetectCollision(BoxCollider*& targetRect) const
{
	if (
		GetRange().left < targetRect->GetRange().right &&
		GetRange().top > targetRect->GetRange().bottom &&
		GetRange().right > targetRect->GetRange().left &&
		GetRange().bottom < targetRect->GetRange().top
		)
	{
		return true;
	}
	else 
		return false;
}


bool BoxCollider::DetectCollision(Vector2& vector) const
{
	//if (m_pGameObject->isActive() == false)
	//	return false;
	if (
		GetRange().left < vector.x &&
		GetRange().right > vector.x &&
		GetRange().top		> vector.y &&
		GetRange().bottom	< vector.y
		)
	{
		return true;
	}
	else
		return false;
}