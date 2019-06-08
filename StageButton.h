#pragma once
#include "GameObject.h"
class StageButton :
	public GameObject
{
public:
	StageButton();
	~StageButton();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetStage(int stageNum);

private:
	void AlignCollider();

	int m_stage;
	float m_totalTime;
	bool m_aniEnd;
	bool m_clicked;
	float m_width;
	float m_height;
};

