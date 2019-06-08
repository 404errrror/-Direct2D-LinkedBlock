#include "stdafx.h"
#include "MoveAbleBlock.h"

std::list<MoveAbleBlock*> MoveAbleBlock::list;

MoveAbleBlock::MoveAbleBlock()
{
	list.push_back(this);
}


MoveAbleBlock::~MoveAbleBlock()
{
}


void MoveAbleBlock::Initialize()
{
	CBlock::Initialize();

	SetId("MoveAbleBlock");
	m_pComponentHub->AddComponent(ComponentHub::RIGIDBODY);
}


void MoveAbleBlock::Release()
{
	CBlock::Release();

	for (std::list<MoveAbleBlock*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}

	delete this;
}


int MoveAbleBlock::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pRectRender->SetColor(D2D1::ColorF(0.37, 0.6, 0.92));
	m_pComponentHub->m_pBoxCollider->SetRange(
		m_pComponentHub->m_pRectRender->GetWidth() - 10,
		m_pComponentHub->m_pRectRender->GetHeight() - 10
		);
	m_pComponentHub->m_pRigidbody->SetMass(0);
	return 0;
}


int MoveAbleBlock::Update()
{
	return 0;
}


int MoveAbleBlock::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	switch (event.GetType())
	{
	case Event::MESSAGE_EVENT:
		if (*(size_t*)event.GetInfo() == g_hasher("Moved"))
		{
			m_pComponentHub->m_pRigidbody->SetMass(0.001);
			AlignPos();
			return 0;
		}
	default:
		break;
	}
	return -1;
}


void MoveAbleBlock::OnCollision(GameObject* gameobject)
{
	if (gameobject->GetId() == g_hasher("WallBlock") || 
		gameobject->GetId() == g_hasher("DieBlock") ||
		gameobject->GetId() == g_hasher("MoveAbleBlock")
		)
	{
		m_pComponentHub->m_pRigidbody->SetMass(-1);
	}
	if (gameobject->GetId() == g_hasher("MyCharacter") &&
		m_pComponentHub->m_pRigidbody->GetMass() == -1)
	{
		AlignPos();
	}

}


void MoveAbleBlock::AlignPos()
{
	Vector2 myPos = m_pComponentHub->m_pTransform->GetPosition();

	if (
		(int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth() > m_pComponentHub->m_pRectRender->GetWidth() * 0.5 ||
		(int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth() < m_pComponentHub->m_pRectRender->GetWidth() * 0.5 * -1
		)
	{
		if (myPos.x > 0)
			myPos.x = (int)myPos.x + m_pComponentHub->m_pRectRender->GetWidth() - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
		else
			myPos.x = (int)myPos.x - m_pComponentHub->m_pRectRender->GetWidth() - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
	}
	else
	{
		myPos.x = (int)myPos.x - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
	}

	if (
		(int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight() > m_pComponentHub->m_pRectRender->GetHeight() * 0.5 ||
		(int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight() < m_pComponentHub->m_pRectRender->GetHeight() * 0.5 * -1
		)
	{
		if (myPos.y > 0)
			myPos.y = (int)myPos.y + m_pComponentHub->m_pRectRender->GetHeight() - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
		else
			myPos.y = (int)myPos.y - m_pComponentHub->m_pRectRender->GetHeight() - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
	}
	else
	{
		myPos.y = (int)myPos.y - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
	}

	m_pComponentHub->m_pTransform->SetPosition(myPos);
}