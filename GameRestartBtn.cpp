#include "stdafx.h"
#include "GameRestartBtn.h"


GameRestartBtn::GameRestartBtn()
{
}


GameRestartBtn::~GameRestartBtn()
{
}


void GameRestartBtn::Initialize()
{
	GameObject::Initialize();
	SetId("RestartBtn");

	m_pComponentHub->AddComponent(ComponentHub::BUTTON);

	m_clicked = false;
	Start();
}


void GameRestartBtn::Release()
{
	GameObject::Release();
	delete this;
}


int GameRestartBtn::Start()
{
	m_pComponentHub->m_pButton->SetImage(g_hasher("RestartBtn_Idle"));
	m_pComponentHub->m_pButton->SetFucusImage(g_hasher("RestartBtn_Focus"));
	m_pComponentHub->m_pButton->SetDownImage(g_hasher("RestartBtn_Press"));

	return 0;
}


int GameRestartBtn::Update()
{
	return 0;
}


int GameRestartBtn::OnEvent(Event& event)
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


bool GameRestartBtn::IsClicked()
{
	return m_clicked;
}