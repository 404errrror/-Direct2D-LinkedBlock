#include "stdafx.h"
#include "EnemySystem.h"


EnemySystem::EnemySystem()
{
	m_repawnTime = 1;
	m_totalTime = 0;
}


EnemySystem::~EnemySystem()
{
}


void EnemySystem::Initialize()
{
	GameObject::Initialize();
	SetId("EnemySystem");

	for (int i = 0; i < 16; ++i)
	{
		m_slimeList.push_back(new Slime());
		m_slimeList.back()->Initialize();
		m_slimeList.back()->SetActive(false);
	}

}


void EnemySystem::Release()
{
	GameObject::Release();

	for (std::list<Slime*>::iterator it = m_slimeList.begin(); it != m_slimeList.end();)
	{
		Slime* tempPtr = *it;
		it = m_slimeList.erase(it);
		tempPtr->Release();
	}
	delete this;
}


int EnemySystem::Start()
{
	//Respawn();	// 여기서 리스폰하면 절대 안됨. 아마 슬라임이 뒤에 Start()호출 되는듯
	return 0;
}


int EnemySystem::Update()
{
	m_repawnTime += Time::GetDeltaTime();
	if (m_repawnTime > 0)
	{
		m_repawnTime = 0;
		Respawn();
	}

	return 0;
}


int EnemySystem::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void EnemySystem::Respawn()
{
	Vector2 respawnPoint;
	respawnPoint.x = CRandom::Range(-1.0, 1.0);
	respawnPoint.y = CRandom::Range(-1.0, 1.0);

	respawnPoint = Vector2::Normalize(respawnPoint) * 1000 ;
	
	for (std::list<Slime*>::iterator it = m_slimeList.begin(); it != m_slimeList.end(); ++it)
	{
		if ((*it)->isActive() == false)
		{
			(*it)->Respawn(respawnPoint);
			break;
		}
	}

}