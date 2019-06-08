#include "stdafx.h"
#include "CollisionEvent.h"


CollisionEvent::CollisionEvent(GameObject* pGameobject)
{
	m_type = Type::COLLISION;
	m_pGameobject = pGameobject;
}


CollisionEvent::~CollisionEvent()
{
}


void* CollisionEvent::GetInfo()
{
	return m_pGameobject;
}