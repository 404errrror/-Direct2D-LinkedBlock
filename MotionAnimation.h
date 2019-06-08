#pragma once
class MotionAnimation :
	public Component
{
public:
	enum Type
	{
		MOTION_ANIMATION_DEAULT,
		MOTION_ANIMATION_SMOOTH_START,
		MOTION_ANIMATION_SMOOTH_END,
		MOTION_ANIMATION_SMOOTH
	};

	MotionAnimation();
	~MotionAnimation();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	static std::list<MotionAnimation*> list;
	
	void SetTime(float);
	// -----> 나중에 smoothMove같은 것들도 추가하기
	void SetMove(Vector2 startPos, Vector2 endPos);
	void SetMove(Vector2 endPos);
	void SetType(Type MOTION_ANIMATION_TYPE);

	bool IsPlay();
	void Play();
	void Stop();

	// 카메라와 같은 원리로 작동하기 때문에
	// 거리와 시간에 따른 적절한 속도값을 넣어주어야함.
	float m_smoothEndSpeed;
private:
	void Move();
	void SmoothMoveStart();
	void SmoothMoveEnd();
	void SmoothMove();


	Transform* m_pTransform;

	float m_time;
	float m_totalTime;
	bool m_isPlay;

	Vector2 m_startPos;
	Vector2 m_endPos;
	Type m_type;

	float m_tEndTime;
	Vector2 m_tStartPos;
};

