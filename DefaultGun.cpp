#include "stdafx.h"
#include "DefaultGun.h"


DefaultGun::DefaultGun()
{
	m_bullet = 8;
	m_remainBullet = 200;
	m_maxBullet = 8;

	m_delay = 1;
	m_reloadDelay = 1;
	m_attack = 2;

	m_bulletArr = new DefaultBullet[10];
	for (int i = 0; i < 10; ++i)
	{
		m_bulletArr[i].Initialize();
		m_bulletArr[i].SetActive(false);
	}
}


DefaultGun::~DefaultGun()
{
}


void DefaultGun::Release()
{
	for (int i = 0; i < 10; ++i)
	{
		m_bulletArr[i].Release();
	}
	delete[] m_bulletArr;
}


int DefaultGun::Shoot()
{

	if (m_bullet > 0)
	{
		--m_bullet;
		for (int i = 0; i < 10; ++i)
		{
			if (m_bulletArr[i].isActive() == false)
			{
				m_bulletArr[i].GetComponentHub()->m_pTransform->SetPosition(g_mouseDesPos + Camera::GetCameraPos());
				m_bulletArr[i].SetActive(true);
				Attack();
				break;
			}
		}

		return 0;
	}
	return -1;
}


int DefaultGun::Reload()
{
	m_remainBullet -= m_maxBullet - m_bullet;
	m_bullet = m_maxBullet;
	return 0;
}


int DefaultGun::GetBullet()
{
	return m_bullet;
}


int DefaultGun::GetRemainBullet()
{
	return m_remainBullet;
}


int DefaultGun::GetMaxBullet()
{
	return m_maxBullet;
}


float DefaultGun::GetDelay()
{
	return m_delay;
}


float DefaultGun::GetReloadDelay()
{
	return m_reloadDelay;
}


void DefaultGun::Attack()
{
	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
	{
		if ((*it)->m_pTransfrom->GetGameobject()->GetComponentHub()->m_pRigidbody &&
			(*it)->DetectCollision((g_mouseDesPos))
			)
		{
			(*it)->m_pTransfrom->GetGameobject()->OnEvent(AttackEvent(&m_attack));
			break;
		}
	}
}