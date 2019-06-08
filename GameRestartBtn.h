#pragma once
#include "GameObject.h"
class GameRestartBtn :
	public GameObject
{
public:
	GameRestartBtn();
	~GameRestartBtn();
	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	bool IsClicked();

private:
	bool m_clicked;
};

