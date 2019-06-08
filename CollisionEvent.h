#pragma once
#include "Event.h"

class GameObject;

class CollisionEvent :
	public Event
{
public:
	CollisionEvent(GameObject* pGameobject);
	~CollisionEvent();

	virtual void* GetInfo();
private:
	GameObject* m_pGameobject;
};

