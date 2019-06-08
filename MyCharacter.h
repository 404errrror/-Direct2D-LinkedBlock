#pragma once
#include "Block.h"
#include "ExplosionEffect.h"
#include "RectRotateEffect.h"
#include "PotalBlock.h"
#include "MoveAbleBlock.h"
class MyCharacter 
	: public CBlock
{
public:
	MyCharacter();
	~MyCharacter();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void OnCollision(GameObject* gameobject);
	bool IsMoveAble();

	static std::list<MyCharacter*> list;
private:
	void MoveControl();
	void AlignPos();
	void Die();
	void FadeOutCharacter();

	Transform* m_pTransform;
	GameObject* coreEffect;
	RectRotateEffect* m_pRotateEffect;
	ExplosionEffect* m_pDieEffect;
	Vector2 m_beforePos;

	bool isDie;
	bool moveEvent;
	float startDelay;
};

