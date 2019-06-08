#include "stdafx.h"
#include "PotalBlock.h"
#include "MyCharacter.h"

std::list<PotalBlock*> PotalBlock::list;

PotalBlock::PotalBlock()
{
	list.push_back(this);
	potalId = 0;
	potalEnable = true;
	m_pPotalEffect = nullptr;
}


PotalBlock::~PotalBlock()
{
}


void PotalBlock::Initialize()
{
	CBlock::Initialize();

	SetId("PotalBlock");
	m_pTransform = m_pComponentHub->m_pTransform;

	m_pPotalEffect = new PotalEffect();
	m_pPotalEffect->Initialize();
}


void PotalBlock::Release()
{
	CBlock::Release();
	m_pPotalEffect->Release();

	for (std::list<PotalBlock*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}


int PotalBlock::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pRectRender->SetColor(D2D1::ColorF(0.3, 0.8, 0.3));
	m_pComponentHub->m_pBoxCollider->SetTrigger(true);

	m_pPotalEffect->GetComponentHub()->m_pTransform->SetParent(m_pTransform);
	m_pPotalEffect->SetSpeed(0.5);
	m_pPotalEffect->SetEffectAmout(2);
	m_pPotalEffect->SetColor(D2D1::ColorF(0.3, 0.8, 0.3));
	m_pPotalEffect->Play();

	return 0;
}


int PotalBlock::Update()
{
	return 0;
}


int PotalBlock::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	switch (event.GetType())
	{
	case Event::MESSAGE_EVENT:
		if (*(size_t*)event.GetInfo() == g_hasher("Moved"))
			SetPotalEnable(true);
		return 0;
	default:
		break;
	}
	return -1;
}


void PotalBlock::OnCollision(GameObject* gameobject)
{
	
	if (gameobject->GetId() == g_hasher("MyCharacter") && potalEnable)
	{
		SetPotalEnable(false);
		for (std::list<PotalBlock*>::iterator it = list.begin(); it != list.end(); ++it)
		{
			if (*it == this)
				continue;
			else if(
				(*it)->GetPotalId() == potalId &&
				Vector2::GetDistance(gameobject->GetComponentHub()->m_pTransform->GetPosition(), m_pComponentHub->m_pTransform->GetPosition()) < 10
				// && gameobject->GetComponentHub()->m_pMotionAnimation->IsPlay() == false
				)
			{
				(*it)->SetPotalEnable(false);
				// Stop 함과 동시에 메세지가 보내지면서 true로 바뀜. 따라서 꾸우욱 눌렀을 때 포탈 왔다갔다하는듯?
				// gameobject->GetComponentHub()->m_pMotionAnimation->Stop();
				gameobject->GetComponentHub()->m_pTransform->SetPosition(
					(*it)->GetComponentHub()->m_pTransform->GetPosition()
					);

				// 만약 두 오브젝트가 겹쳤다면 위치 스왑
				for (std::list<MyCharacter*>::iterator it = MyCharacter::list.begin(); it != MyCharacter::list.end(); ++it)
				{
					if (*it == gameobject)
						continue;
					else if (Vector2::GetDistance(
							(*it)->GetComponentHub()->m_pTransform->GetPosition(),
							gameobject->GetComponentHub()->m_pTransform->GetPosition()) < 10)
					{
						(*it)->GetComponentHub()->m_pTransform->SetPosition(
							m_pComponentHub->m_pTransform->GetPosition()
							);
					}
				} // < MyCharacter For() />

			} // < PotalBlock For() />
		}
	}


} // < OnCollision />


void PotalBlock::SetPotalEnable(bool enable)
{
	potalEnable = enable;
}


void PotalBlock::SetPotalId(int id)
{
	potalId = id;
}


int PotalBlock::GetPotalId()
{
	return potalId;
}