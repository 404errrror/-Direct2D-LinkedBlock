#include "stdafx.h"
#include "StartButton.h"


StartButton::StartButton()
{
	m_clicked = false;
}


StartButton::~StartButton()
{
}

void StartButton::Initialize()
{
	GameObject::Initialize();
	SetId("StartButton");

	m_pComponentHub->AddComponent(ComponentHub::BUTTON);
	Start();
}


void StartButton::Release()
{
	GameObject::Release();
	delete this;
}


int StartButton::Start()
{
	m_pComponentHub->m_pButton->SetImage(g_hasher("StartBtnImg_Idle"));
	m_pComponentHub->m_pButton->SetFucusImage(g_hasher("StartBtnImg_Focus"));
	m_pComponentHub->m_pButton->SetDownImage(g_hasher("StartBtnImg_Press"));

	m_pComponentHub->m_pTransform->SetPosition(Vector2(0, -75));
	return 0;
}


int StartButton::Update()
{
	return 0;
}


int StartButton::OnEvent(Event& event)
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


bool StartButton::IsClicked()
{
	return m_clicked;
}