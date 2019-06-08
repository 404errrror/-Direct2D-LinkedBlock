#pragma once
#include "GunInterface.h"
#include "DefaultBullet.h"
#include "AttackEvent.h"
class DefaultGun :
	public GunInterface
{
public:
	DefaultGun();
	~DefaultGun();

	void Release();

	virtual int Shoot();
	virtual int Reload();

	virtual int GetBullet();
	virtual int GetRemainBullet();
	virtual int GetMaxBullet();

	virtual float GetDelay();
	virtual float GetReloadDelay();
private:
	void Attack();

	int m_bullet;
	int m_remainBullet;
	int m_maxBullet;
	float m_delay;
	float m_reloadDelay;

	int m_attack;

	DefaultBullet* m_bulletArr;
};

