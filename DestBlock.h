#pragma once
#include "Block.h"
#include "PotalEffect.h"
class DestBlock
	: public CBlock
{
public:
	DestBlock();
	~DestBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);
	virtual void OnCollision(GameObject* gameobject);

	bool IsDest();

	static std::list<DestBlock*> list;
private:
	//void DestCheck();
	void EffectChange();

	bool m_dest;
	PotalEffect* m_pPotalEffect;
	PotalEffect* m_pDestEffect;

	D2D1_COLOR_F* m_defaultColor;
	D2D1_COLOR_F* m_destColor;
};

