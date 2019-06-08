#pragma once
#include <list>


class FrameAnimation : public Component
{
public:
	FrameAnimation();
	~FrameAnimation();

	virtual void Initialize	(GameObject*);
	virtual void Release	();

	virtual int Start		();
	virtual int Update		();
	virtual int OnEvent		(Event&);

	void AddImage			(size_t animationState, size_t animationImageId);
	// 애니메이션 상태를 설정합니다.
	void SetState			(size_t);
	void SetState			(std::string);
	void SetReplay			(bool);

	bool isPlay()const;
	void Play();
	void Stop();

	size_t	GetState		()const;

	static std::list<FrameAnimation*> list;
private:
	Image*										m_pImageComponent;
	std::map<size_t, std::list<size_t>>			m_animationData;
	std::list<size_t>::iterator					m_iterator;
	size_t										m_state;
	float										m_delay;
	float										m_time;
	bool										m_replay;
	bool										m_end;
};

