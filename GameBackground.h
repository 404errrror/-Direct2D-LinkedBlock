#pragma once
#include "GameObject.h"
class GameBackground :
	public GameObject
{
public:
	GameBackground();
	~GameBackground();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

private:
	void ObjectSetting(GameObject*& gameobject);

	GameObject* m_pRock;
	GameObject* m_pTree;
	GameObject* m_pHalfTree;
	GameObject* m_pFire;
};

