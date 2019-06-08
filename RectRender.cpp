#include "stdafx.h"
#include "RectRender.h"

std::list<RectRender*> RectRender::list;

RectRender::RectRender()
{
	list.push_back(this);

	m_pTransform = nullptr;
	m_pBrush = nullptr;
	m_isFill = false;
	m_strokeWidth = 1;
	m_width = 0;
	m_height = 0;

	m_matrix = { 1, 0, 0, 1, 0, 0 };
}


RectRender::~RectRender()
{
}


void RectRender::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);

	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;
}


void RectRender::Release()
{
	Component::Release();

	for (std::list<RectRender*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == this)
		{
			list.erase(it);
			break;
		}
	}
	m_pBrush->Release();
	delete this;
}


int RectRender::Start()
{
	Refresh();
	if (m_pBrush == nullptr)
		GameObject::GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &m_pBrush);

	return 0;
}


int RectRender::Update()
{
	if (m_pGameObject->isActive() == false)
		return 0;

	if (m_enable == false)
		return 0;

	D2D1_RECT_F screenRectPos;
	screenRectPos = D2D1::RectF(
		m_pTransform->GetScreenPosition().x - m_width * 0.5 - Camera::GetCameraPos().x,
		m_pTransform->GetScreenPosition().y + m_height * 0.5 + Camera::GetCameraPos().y,
		m_pTransform->GetScreenPosition().x + m_width * 0.5 - Camera::GetCameraPos().x,
		m_pTransform->GetScreenPosition().y - m_height * 0.5 + Camera::GetCameraPos().y
		);

	Refresh();
	GameObject::GetRenderTarget()->SetTransform(m_matrix);

	if (m_isFill)
	{
		if(m_pGameObject->IsMask())
			GameObject::GetMask()->FillRectangle(screenRectPos, m_pBrush);
		else
			GameObject::GetRenderTarget()->FillRectangle(screenRectPos, m_pBrush);
	}
	else
	{
		if (m_pGameObject->IsMask())
		{
			GameObject::GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1,1), &m_pBrush);
			GameObject::GetMask()->DrawRectangle(screenRectPos, m_pBrush, m_strokeWidth);
		}
		else
			GameObject::GetRenderTarget()->DrawRectangle(screenRectPos, m_pBrush, m_strokeWidth);
	}


	

	GameObject::GetRenderTarget()->SetTransform(g_defaultMatrix);
	return 0;
}


int RectRender::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:
		SetColor(m_pBrush->GetColor());
		Refresh();
		return 0;
	default:
		break;
	}
	return -1;
}


//void RectRender::SetWidth(float width)
//{
//	m_width = width;
//}
//
//
//void RectRender::SetHeight(float height)
//{
//	m_height = height;
//}


void RectRender::SetColor(D2D1_COLOR_F& color)
{
	RELEASE(m_pBrush);
	GameObject::GetRenderTarget()->CreateSolidColorBrush(color, &m_pBrush);
}


void RectRender::SetStrokeWidth(float width)
{
	m_strokeWidth = width;
}


void RectRender::SetFill(bool isFill)
{
	m_isFill = isFill;
}


void RectRender::AlignCollider()
{
	m_pGameObject->GetComponentHub()->m_pBoxCollider->SetRange(D2D1::RectF(
		m_width * -0.5,
		m_height * 0.5,
		m_width * 0.5,
		m_height* -0.5));
}

void RectRender::Refresh()
{
	m_width = 100 * m_pTransform->GetScale().x;
	m_height = 100 * m_pTransform->GetScale().y;

	D2D1_POINT_2F centerPos = m_pTransform->GetScreenPosition();
	Camera::Apply(centerPos);
	// 회전 행렬
	m_matrix = D2D1::Matrix3x2F::Rotation(m_pTransform->GetRotation(), centerPos) * g_defaultMatrix;
	
}

float RectRender::GetWidth()
{
	return m_width;
}


float RectRender::GetHeight()
{
	return m_height;
}


D2D1_COLOR_F RectRender::GetColor()
{
	return m_pBrush->GetColor();
}