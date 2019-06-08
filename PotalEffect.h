#pragma once
#include "GameObject.h"
class PotalEffect :
	public GameObject
{
public:
	PotalEffect();
	~PotalEffect();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetEffectAmout		(int amount);
	void SetColor			(D2D1_COLOR_F);
	// �ӵ��� �����մϴ�. speed 1 = 1��, speed 2 = 0.5��
	void SetSpeed			(float speed, float alphaSpeed = 0);
	// True ���� �����. False ���� ��Ÿ��.
	void SetFade			(bool);
	void SetScale			(Vector2 start, Vector2 end);
	void SetAnimationType(ShapeAnimation::AnimationType);
	
	void Play();
	bool IsPlay();
	void Stop();
private:
	Transform* m_pTransform;

	GameObject* m_effectArr;
	D2D1_COLOR_F* m_colorArr;
	D2D1_COLOR_F m_baseColor;

	int		m_amount;
	float	m_speed;
	float	m_alphaSpeed;
	float	m_totalTime;
	bool	m_fadeIn;
	Vector2 m_startScale;
	Vector2 m_endScale;
	bool	m_isPlay;
};

