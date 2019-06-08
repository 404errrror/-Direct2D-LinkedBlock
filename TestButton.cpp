#include "stdafx.h"
#include "TestButton.h"


TestButton::TestButton()
{
}


TestButton::~TestButton()
{
}


void TestButton::Initialize()
{
	GameObject::Initialize();
	SetId("Button");

	m_pComponentHub->AddComponent(ComponentHub::BUTTON);
	Start();
}


void TestButton::Release()
{
	GameObject::Release();
}


int TestButton::Start()
{
	m_pComponentHub->m_pButton->SetImage(g_hasher("StartBtnImg"));
	m_pComponentHub->m_pButton->SetFucusImage(g_hasher("StartBtnFocusImg"));
	m_pComponentHub->m_pButton->SetDownImage(g_hasher("StartBtnDownImg"));
	m_pComponentHub->m_pButton->SetScale(Vector2(0.5, 0.5));
	return 0;
}


int TestButton::Update()
{
	return 0;
}


int TestButton::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	switch (event.GetType())
	{
	case Event::Type::BUTTON_CLICK:
		
		for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		{
			if ((*it)->GetName() == "TestCharacter")
			{
				(*it)->GetComponentHub()->m_pTransform->SetPosition(Vector2(0, 0));
				break;
			}
		}

		return 0;
	default:
		break;
	}
	return -1;
}