#pragma once
#include "GameObject.h"
class Character :
	public GameObject
{
public:
	Character();
	~Character();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	// 급해서 전역변수로.
	static int m_hp;
private:
	GameObject* m_pHpText;
	Vector2 m_screenSize;
};

