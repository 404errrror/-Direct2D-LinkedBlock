#pragma once
class GameObject;

class Component
{
public:
	Component();
	~Component();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start		() = 0;
	virtual int Update		() = 0;
	virtual int OnEvent		(Event&) = 0;

	void SetEnable(bool);
	bool IsEnable();

protected:
	bool			m_enable;
	GameObject*		m_pGameObject;
};

