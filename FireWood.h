#pragma once
#include "GameObject.h"
#include "Light.h"
class FireWood :
	public GameObject
{
public:
	FireWood();
	~FireWood();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

private:
	Light* m_pLight;
	float lightPercent;
};

