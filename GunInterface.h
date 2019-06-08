#pragma once
#include "ShootInterface.h"
class GunInterface :
	public ShootInterface
{
public:
	virtual int Shoot() = 0;
	virtual int Reload() = 0;

	virtual int GetBullet() = 0;
	virtual int GetRemainBullet() = 0;
	virtual int GetMaxBullet() = 0;
	virtual float GetDelay() = 0;
	virtual float GetReloadDelay() = 0;
};

