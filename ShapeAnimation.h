#pragma once
class ShapeAnimation : public Component
{
public:
	enum AnimationType
	{
		ANIMATION_DEFAULT,
		ANIMATION_SMOOTH_START,
		ANIMATION_SMOOTH_END,
		ANIMATION_SMOOTH
	};
	ShapeAnimation();
	~ShapeAnimation();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetAnimationType	(AnimationType);
	void SetTime			(float);
	void SetScale			(Vector2 startScale, Vector2 endScale);
	void SetScale			(Vector2 endScale);
	//void SetStartScale		(Vector2 scale);
	//void SetEndScale		(Vector2 scale);

	bool IsPlay();
	void Play();
	void Stop();

	static std::list<ShapeAnimation*> list;
private:

	void Default();
	void SmoothStart();
	void SmoothEnd();

	Transform*		m_pTransform;
	AnimationType	m_animationType;

	Vector2 m_startScale;
	Vector2 m_endScale;
	float	m_time,			m_totalTime;

	bool m_isPlay;
};

