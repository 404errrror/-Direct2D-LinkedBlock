#pragma once
#include "ShootInterface.h"
#include "ShootPoint.h"
#include "GunSystem.h"

class ShootSystem :
	public ShootInterface
{
public:
	ShootSystem();
	~ShootSystem();

	virtual int Shoot();
	virtual int Reload();

	void Initialize();
	void Release();

private:
	GunSystem* m_pBulletCount;
};