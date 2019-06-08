#pragma once
#include "Block.h"
class WallBlock
	: public CBlock
{
public:
	WallBlock();
	~WallBlock();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

};

