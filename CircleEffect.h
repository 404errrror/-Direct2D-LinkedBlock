#pragma once
#include "GameObject.h"
class CircleEffect :
	public GameObject
{
public:
	enum Type
	{
		TYPE_NONE,
		TYPE_MASK
	};

	CircleEffect();
	~CircleEffect();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();

	void SetType(Type);
	void SetScale(Vector2 endScale);
	void SetScale(Vector2 startScale, Vector2 endScale);
	void SetColor(D2D1_COLOR_F);
	void SetTime(float);

	void Play();
	bool IsPlay();
	void Stop();

private:
	Type m_type;
	bool m_isPlay;
	Vector2 m_endScale;
	Vector2	m_startScale;
	D2D1_COLOR_F m_color;
	float m_time;
};

