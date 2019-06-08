#pragma once
#include "GameObject.h"
class DefaultBullet :
	public GameObject
{
public:
	DefaultBullet();
	~DefaultBullet();
	
	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

private:

};

