#include "stdafx.h"
#include "AttackEvent.h"


AttackEvent::AttackEvent(int* attack)
{
	m_type = ATTACK;
	m_pAttack = attack;
}


AttackEvent::~AttackEvent()
{
}


void* AttackEvent::GetInfo()
{
	return m_pAttack;
}