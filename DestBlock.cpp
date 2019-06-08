#include "stdafx.h"
#include "DestBlock.h"

std::list<DestBlock*> DestBlock::list;

DestBlock::DestBlock()
{
	list.push_back(this);
	m_dest = false;
}


DestBlock::~DestBlock()
{
}


void DestBlock::Initialize()
{
	CBlock::Initialize();

	SetId("DestBlock");

	m_pPotalEffect = new PotalEffect();
	m_pPotalEffect->Initialize();
	m_pDestEffect = new PotalEffect();
	m_pDestEffect->Initialize();

	m_defaultColor = new D2D1::ColorF(1, 0.7, 0.3);
	m_destColor = new D2D1::ColorF(0.7, 0.95, 0.45);
}


void DestBlock::Release()
{
	CBlock::Release();

	for (std::list<DestBlock*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	m_pPotalEffect->Release();
	m_pDestEffect->Release();

	delete m_defaultColor;
	delete m_destColor;
	delete this;
}


int DestBlock::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pRectRender->SetColor(*m_defaultColor);
	m_pComponentHub->m_pBoxCollider->SetTrigger(true);

	m_pPotalEffect->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pPotalEffect->SetColor(*m_defaultColor);
	m_pPotalEffect->SetEffectAmout(3);
	m_pPotalEffect->SetFade(true);
	m_pPotalEffect->SetScale(Vector2(3, 3), Vector2(1, 1));
	m_pPotalEffect->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_START);
	m_pPotalEffect->Play();

	m_pDestEffect->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pDestEffect->SetColor(*m_destColor);
	m_pDestEffect->SetEffectAmout(3);
	m_pDestEffect->SetFade(false);
	m_pDestEffect->SetScale(Vector2(1, 1), Vector2(3, 3));
	m_pDestEffect->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);
	m_pDestEffect->Play();
	return 0;
}


int DestBlock::Update()
{
	if (m_dest)
	{
		if (m_pPotalEffect->IsPlay())
			EffectChange();
		m_pComponentHub->m_pRectRender->SetColor(*m_destColor);
		m_pPotalEffect->SetColor(*m_destColor);

	}
	else
	{
		if (m_pDestEffect->IsPlay())
			EffectChange();
		m_pComponentHub->m_pRectRender->SetColor(*m_defaultColor);
		m_pPotalEffect->SetColor(*m_defaultColor);
	}
	return 0;
}


int DestBlock::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	switch (event.GetType())
	{
	case Event::MESSAGE_EVENT:
		if (*(size_t*)event.GetInfo() == g_hasher("Moved"))
			m_dest = false;
		return 0;
	}
	return -1;
}


//void DestBlock::DestCheck()
//{
//	m_dest = false;
//
//	for (std::list<MyCharacter*>::iterator it = MyCharacter::list.begin(); it != MyCharacter::list.end(); ++it)
//	{
//		if (Vector2::GetDistance(
//			(*it)->GetComponentHub()->m_pTransform->GetPosition(),
//			m_pComponentHub->m_pTransform->GetPosition())
//			< 10)
//		{
//			m_dest = true;
//			break;
//		}
//	}
//
//
//}


void DestBlock::OnCollision(GameObject* gameobject)
{
	if (gameobject->GetId() == g_hasher("MyCharacter") &&
		Vector2::GetDistance(
			gameobject->GetComponentHub()->m_pTransform->GetPosition(),
			m_pComponentHub->m_pTransform->GetPosition())
			== 0)
	{
		m_dest = true;
	}
}


bool DestBlock::IsDest()
{
	return m_dest;
}


void DestBlock::EffectChange()
{
	if (m_pPotalEffect->IsPlay())
	{
		m_pDestEffect->Play();
		m_pPotalEffect->Stop();
	}
	else
	{
		m_pDestEffect->Stop();
		m_pPotalEffect->Play();
	}
}