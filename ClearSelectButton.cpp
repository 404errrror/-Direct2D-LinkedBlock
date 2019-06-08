#include "stdafx.h"
#include "ClearSelectButton.h"


ClearSelectButton::ClearSelectButton()
{
	m_clicked = false;
	m_imageWidth = 0;
	m_imageHeight = 0;
}


ClearSelectButton::~ClearSelectButton()
{
}


void ClearSelectButton::Initialize()
{
	GameObject::Initialize();
	SetId("ClearSelectButton");

	m_pComponentHub->AddComponent(ComponentHub::BUTTON);
	m_pComponentHub->AddComponent(ComponentHub::SHAPE_ANIMATION);
	Start();
}


void ClearSelectButton::Release()
{
	GameObject::Release();
	delete this;
}


int ClearSelectButton::Start()
{
	m_pComponentHub->m_pButton->SetImage(g_hasher("Clear_SelectBtn_Idle"));
	m_pComponentHub->m_pButton->SetFucusImage(g_hasher("Clear_SelectBtn_Focus"));
	m_pComponentHub->m_pButton->SetDownImage(g_hasher("Clear_SelectBtn_Press"));
	m_imageWidth = m_pComponentHub->m_pImage->GetImageWidth();
	m_imageHeight = m_pComponentHub->m_pImage->GetImageHeight();

	m_pComponentHub->m_pShapeAnimation->SetScale(Vector2(0, 0), Vector2(1, 1));
	m_pComponentHub->m_pShapeAnimation->SetTime(0.5);
	m_pComponentHub->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);
	m_pComponentHub->m_pTransform->SetPosition(Vector2(0, -200));
	SetActive(false);
	return 0;
}


int ClearSelectButton::Update()
{
	if(m_pComponentHub->m_pGameObject->isActive())
		AlignCollider();
	return 0;
}


int ClearSelectButton::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	switch (event.GetType())
	{
	case Event::Type::BUTTON_CLICK:
		m_clicked = true;
		return 0;
	default:
		break;
	}
	return -1;
}


bool ClearSelectButton::IsClicked()
{
	return m_clicked;
}


void ClearSelectButton::AlignCollider()
{
	m_pComponentHub->m_pBoxCollider->SetRange(
		m_imageWidth * m_pComponentHub->m_pTransform->GetScale().x * m_pComponentHub->m_pTransform->GetParent()->GetScale().x,
		m_imageHeight * m_pComponentHub->m_pTransform->GetScale().y * m_pComponentHub->m_pTransform->GetParent()->GetScale().y
		);
}