#pragma once
#include "GameObject.h"
class Light :
	public GameObject
{
public:
	Light();
	~Light();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void ChageLight(float strength);
private:
	CircleRender* m_pCircleRender;
	float m_minLight;
	float m_maxLight;
	float m_totalTime;
	float m_delayTime;
	float m_nowStrength;
};

