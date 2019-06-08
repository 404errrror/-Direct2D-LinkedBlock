#pragma once
#include "GameObject.h"
#include "EnemyInterface.h"
class Slime :
	public GameObject, public EnemyInterface
{
public:
	Slime();
	~Slime();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	virtual void Attack();
	virtual void Die();
	virtual void Hitted(int attack);
	virtual void Respawn(Vector2);

private:
	Transform* m_pTransform;
	FrameAnimation* m_pFrameAnimation;
	float m_hittedAniTime;
	bool m_isDie;
	bool m_moveAble;
	bool m_isAttacking;
	float m_attackTime;
};

