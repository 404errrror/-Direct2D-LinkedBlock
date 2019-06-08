#pragma once
#include "Block.h"
class MoveAbleBlock :
	public CBlock
{
public:
	MoveAbleBlock();
	~MoveAbleBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);
	virtual void OnCollision(GameObject* gameobject);

	static std::list<MoveAbleBlock*> list;
private:
	void AlignPos();
};

