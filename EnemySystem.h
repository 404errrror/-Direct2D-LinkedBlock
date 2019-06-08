#pragma once
#include "GameObject.h"
#include "EnemyInterface.h"
#include "Slime.h"
class EnemySystem :
	public GameObject
{
public:
	EnemySystem();
	~EnemySystem();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

private:
	void Respawn();

	std::list<Slime*> m_slimeList;
	float m_repawnTime;
	float m_totalTime;
};

