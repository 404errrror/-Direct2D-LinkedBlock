#pragma once
#include "GameObject.h"
class CBlock :
	public GameObject
{
public:
	CBlock();
	~CBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update() { return 0; };
	virtual int OnEvent(Event&);

};

