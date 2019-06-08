#pragma once
#include "Block.h"
#include "RectRotateEffect.h"
class DieBlock : 
	public CBlock
{
public:
	DieBlock();
	~DieBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void OnCollision(GameObject* gameobject);
private:
	RectRotateEffect* m_pRotateEffect;
};

