#pragma once
#include "GameObject.h"
class StartButton :
	public GameObject
{
public:
	StartButton();
	~StartButton();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	bool IsClicked();

private:
	bool m_clicked;
};

