#include "stdafx.h"
#include "ShootSystem.h"


ShootSystem::ShootSystem()
{
}


ShootSystem::~ShootSystem()
{
}


int ShootSystem::Shoot()
{
	return -1;
}


int ShootSystem::Reload()
{
	return -1;
}


void ShootSystem::Initialize()
{
	m_pBulletCount = new GunSystem();
	m_pBulletCount->Initialize();
}


void ShootSystem::Release()
{
}