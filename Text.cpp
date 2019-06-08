#include "stdafx.h"
#include "Text.h"
#include "D2DClass.h"

std::list<Text*> Text::list;
IDWriteFactory* Text::pTextFactory = nullptr;

Text::Text()
{
	list.push_back(this);
	m_pTransform = nullptr;
	m_pTextFormat = nullptr;
	m_pTextLayout = nullptr;
	m_pColorBrush = nullptr;
	m_pText = "NULL";
	m_textSize = 50;
	m_layoutWidth = 1000;
	m_layoutHeight = 500;
}

 
Text::~Text()
{
}


void Text::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;

	if (pTextFactory == nullptr)
	{
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pTextFactory),
			reinterpret_cast<IUnknown **>(&pTextFactory)
			);
	}

	pTextFactory->CreateTextFormat(
		L"돋움",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_textSize,
		L"",
		&m_pTextFormat
		);

	// 텍스트 정렬
	// _CENTER = 가운데 정렬
	// _JUSTIFIED = 그 그냥 정렬하는거. 적당히 알아서 글자 사이 공간 맞춰주는?
	// _LEADING = 좌측 정렬
	// _TRAILING = 우측 정렬
	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	// 단락의 위치
	//_NEAR = 윗쪽 가장자리
	// _FAR = 아랫쪽 가장자리
	// _CENTER = 가운데
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	pTextFactory->CreateTextLayout(m_pText, m_pText.GetLength(), m_pTextFormat, m_layoutWidth, m_layoutHeight, &m_pTextLayout);

	if (m_pColorBrush == nullptr)
		GameObject::GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &m_pColorBrush);
}


void Text::Release()
{
	Component::Release();
	for (std::list<Text*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}

	m_pTextFormat->Release();
	m_pTextLayout->Release();
	// CString 은 Release 해줘야하나?
	delete this;
}


int Text::Start()
{
	return 0;
}


int Text::Update()
{
	Vector2 temp = m_pTransform->GetPosition();
	Camera::Apply(temp);


	if (m_pGameObject->IsUi())
	{
		GameObject::GetUiRenderTarget()->DrawTextLayout(
			temp.GetScreenVector(),
			m_pTextLayout, m_pColorBrush
			);
	}
	else
	{
		GameObject::GetRenderTarget()->DrawTextLayout(
			temp.GetScreenVector(),
			m_pTextLayout, m_pColorBrush
			);
	}
	if (g_debugMode)
		Debug();

	return 0;
}

void Text::Debug()
{
	Vector2 temp = m_pTransform->GetPosition();
	Camera::Apply(temp);

	if (m_pGameObject->IsUi())
	{
		GameObject::GetUiRenderTarget()->DrawRectangle(
			D2D1::RectF(
				temp.GetScreenVector().x,
				temp.GetScreenVector().y,
				temp.GetScreenVector().x + m_layoutWidth,
				temp.GetScreenVector().y + m_layoutHeight
				),
			D2DClass::GetSolidBrush(D2D1::ColorF(1, 0, 0))
			);
	}
	else		// ---------> 요 밑에 애는 작동되는지 확인 안해봄. 나중에 해보기.
	{
		GameObject::GetRenderTarget()->DrawRectangle(
			D2D1::RectF(
				temp.GetScreenVector().x,
				temp.GetScreenVector().y,
				temp.GetScreenVector().x + m_layoutWidth,
				temp.GetScreenVector().y + m_layoutHeight
				),
			D2DClass::GetSolidBrush(D2D1::ColorF(1, 0, 0))
			);
	}
	

}



int Text::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:
	{
		float tempOpacity = m_pColorBrush->GetOpacity();
		GameObject::GetRenderTarget()->CreateSolidColorBrush(m_pColorBrush->GetColor(), &m_pColorBrush);
		m_pColorBrush->SetOpacity(tempOpacity);
	}
		return 0;
	default:
		break;
	}
	return -1;
}


void Text::SetText(const char* str)
{
	m_pText = str;
	m_pTextLayout->Release();

	pTextFactory->CreateTextLayout(
		m_pText, 
		m_pText.GetLength(), 
		m_pTextFormat, 
		m_layoutWidth,
		m_layoutHeight,
		&m_pTextLayout
		);
}


void Text::SetTextSize(float size)
{
	m_textSize = size;

	// 얼마나 텍스트를 변경할 것인지. 지금은 그냥 다 변경.
	DWRITE_TEXT_RANGE textRange;
	textRange.startPosition = 0;
	textRange.length = m_pText.GetLength();

	m_pTextLayout->SetFontSize(m_textSize, textRange);
}


void Text::SetWidth(float width)
{
	m_layoutWidth = width;
	m_pTextLayout->SetMaxWidth(m_layoutWidth);
}


void Text::SetHeight(float height)
{
	m_layoutHeight = height;
	m_pTextLayout->SetMaxHeight(m_layoutHeight);
}


void Text::SetColor(D2D1_COLOR_F color)
{
	m_pColorBrush->SetColor(color);
}


void Text::SetOpacity(float opacity)
{
	m_pColorBrush->SetOpacity(opacity);
}


void Text::SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlign)
{
	m_pTextFormat->SetTextAlignment(textAlign);
	pTextFactory->CreateTextLayout(
		m_pText,
		m_pText.GetLength(),
		m_pTextFormat,
		m_layoutWidth,
		m_layoutHeight,
		&m_pTextLayout
		);
}


D2D1_COLOR_F Text::GetColor() const
{
	return m_pColorBrush->GetColor();
}


float Text::GetOpacity() const
{
	return m_pColorBrush->GetOpacity();
}