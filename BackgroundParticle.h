#pragma once
#include "GameObject.h"
class BackgroundParticle :
	public GameObject
{
public:
	BackgroundParticle();
	~BackgroundParticle();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetAmount(int);
	void SetCamera(Transform*);
	void Generate();
private:
	GameObject* m_particleArr;
	Vector2* m_posArr;
	float* m_zArr;
	Transform* m_pCameraTarget;
	int m_amount;
	bool m_generated;
};

