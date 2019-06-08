#pragma once
#include "GameObject.h"
class ShootPoint :
	public GameObject
{
public:
	ShootPoint();
	~ShootPoint();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

};

