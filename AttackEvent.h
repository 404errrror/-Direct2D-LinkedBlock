#pragma once
#include "Event.h"
class AttackEvent :
	public Event
{
public:
	AttackEvent(int* attack);
	~AttackEvent();

	virtual void* GetInfo();
private:
	int* m_pAttack;
};

