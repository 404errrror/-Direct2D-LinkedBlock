#pragma once
#include "PotalEffect.h"
#include "Block.h"
class PotalBlock
	: public CBlock
{
public:
	PotalBlock();
	~PotalBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	virtual void OnCollision(GameObject* gameobject);

	void SetPotalEnable(bool enable);
	void SetPotalId(int id);

	int GetPotalId();

	static std::list<PotalBlock*> list;
private:
	Transform* m_pTransform;

	int potalId;
	bool potalEnable;
	PotalEffect* m_pPotalEffect;
};

