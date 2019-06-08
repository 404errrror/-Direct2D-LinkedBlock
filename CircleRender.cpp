#include "stdafx.h"
#include "CircleRender.h"

std::list<CircleRender*> CircleRender::list;

CircleRender::CircleRender()
{
	list.push_back(this);

	m_pTransform = nullptr;
	m_pBrush = nullptr;
	m_pGradientBrush = nullptr;
	m_matrix = { 1, 0, 0, 1, 0, 0 };
	m_isFill = false;
	m_isGradient = false;
	m_strokeWidth = 1;
	m_width = 0;
	m_height = 0;
}


CircleRender::~CircleRender()
{
}


void CircleRender::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;

}


void CircleRender::Release()
{
	Component::Release();
	for (std::list<CircleRender*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	m_pBrush->Release();
	delete this;
}


int CircleRender::Start()
{
	Refresh();
	if (m_pBrush == nullptr)
		GameObject::GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &m_pBrush);
	
	if (m_pGradientBrush == nullptr)
	{
		MakeRadialGradientBrush(
			m_pBrush->GetColor(),
			D2D1::ColorF(
			m_pBrush->GetColor().r,
			m_pBrush->GetColor().g,
			m_pBrush->GetColor().b,
			0),
			m_pGradientBrush
			);
	}

	return 0;
}


int CircleRender::Update()
{
	if (m_enable == false || m_pGameObject->isActive() == false)
		return 0;

	D2D1_POINT_2F screenRectPos = m_pTransform->GetScreenPosition();
	Camera::Apply(screenRectPos);

	if (m_isFill)
	{
		if(m_pGameObject->IsMask())
			GameObject::GetMask()->FillEllipse(
				D2D1::Ellipse(
					screenRectPos,
					m_width * 0.5, m_height * 0.5
					),
				m_pBrush
				);
		else
			GameObject::GetRenderTarget()->FillEllipse(
				D2D1::Ellipse(
				screenRectPos,
				m_width * 0.5, m_height * 0.5
				),
				m_pBrush
				);
	}
	else if (m_isGradient)
	{
		if (m_pGameObject->IsMask())
		{
			m_pGradientBrush->SetCenter(screenRectPos);
			GameObject::GetMask()->FillEllipse(
				D2D1::Ellipse(
				screenRectPos,
				m_pGradientBrush->GetRadiusX(), m_pGradientBrush->GetRadiusY()
				),
				m_pGradientBrush
				);
		}
		else
		{
			m_pGradientBrush->SetCenter(screenRectPos);
			GameObject::GetRenderTarget()->FillEllipse(
				D2D1::Ellipse(
				screenRectPos,
				m_pGradientBrush->GetRadiusX(), m_pGradientBrush->GetRadiusY()
				),
				m_pGradientBrush
				);
		}

	}
	else
	{
		if(m_pGameObject->IsMask())
			GameObject::GetMask()->DrawEllipse(
				D2D1::Ellipse(
					screenRectPos,
					m_width * 0.5, m_height * 0.5
					),
				m_pBrush
				);
		else
			GameObject::GetRenderTarget()->DrawEllipse(
				D2D1::Ellipse(
					screenRectPos,
				m_width * 0.5, m_height * 0.5
				),
				m_pBrush
				);
	}

	return 0;
}


int CircleRender::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:

		SetColor(m_pBrush->GetColor());
		return 0;

	case Event::GAMEOBJECT_TRANSFORM_CHANGE:
		Refresh();
		return 0;
	default:
		break;
	}

	return -1;
}


void CircleRender::SetColor(D2D1_COLOR_F& color)
{
	RELEASE(m_pBrush);

	GameObject::GetRenderTarget()->CreateSolidColorBrush(color, &m_pBrush);

	if (m_isGradient)
	{
		RELEASE(m_pGradientBrush);
		MakeRadialGradientBrush(
			m_pBrush->GetColor(),
			D2D1::ColorF(
			m_pBrush->GetColor().r,
			m_pBrush->GetColor().g,
			m_pBrush->GetColor().b,
			0),
			m_pGradientBrush
			);
	}
}


void CircleRender::SetStrokeWidth(float width)
{
	m_strokeWidth = width;
}


void CircleRender::SetFill(bool isFill)
{
	m_isFill = isFill;
}


void CircleRender::SetGraident(bool isGradient)
{
	m_isGradient = isGradient;
}


void CircleRender::AlignCollider()
{
	m_pGameObject->GetComponentHub()->m_pBoxCollider->SetRange(D2D1::RectF(
		m_width * -0.5,
		m_height * 0.5,
		m_width * 0.5,
		m_height* -0.5));
}


void CircleRender::Refresh()
{
	m_width = 100 * m_pTransform->GetScale().x;
	m_height = 100 * m_pTransform->GetScale().y;

	// 회전 행렬
	m_matrix = D2D1::Matrix3x2F::Rotation(m_pTransform->GetRotation(), m_pTransform->GetScreenPosition()) * g_defaultMatrix;

	if (m_isGradient&& m_pGradientBrush)
	{
		m_pGradientBrush->SetRadiusX(m_width);
		m_pGradientBrush->SetRadiusY(m_height);
	}
}


D2D1_COLOR_F CircleRender::GetColor() const
{
	return m_pBrush->GetColor();
}


float CircleRender::GetWidth() const
{
	return m_width;
}


float CircleRender::GetHeight() const
{
	return m_height;
}


void CircleRender::MakeRadialGradientBrush(
	const D2D1_COLOR_F& centerColor,
	const D2D1_COLOR_F& edgeColor,
	ID2D1RadialGradientBrush*& radiaGradientBrush
	)
{
	ID2D1GradientStopCollection* pGradientStops; //색상

	D2D1_GRADIENT_STOP gradientStops[2];
	HRESULT hr;

	gradientStops[0].color = centerColor;
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = edgeColor;
	gradientStops[1].position = 1.0f;


	GameObject::GetRenderTarget()->CreateGradientStopCollection(gradientStops, 2, &pGradientStops);

	GameObject::GetRenderTarget()->CreateRadialGradientBrush(
		D2D1::RadialGradientBrushProperties(
		D2D1::Point2F(300, 300), 
		D2D1::Point2F(0, 0), 
		m_width, m_height
		),
	pGradientStops,
	&radiaGradientBrush
	);

	pGradientStops->Release();
}