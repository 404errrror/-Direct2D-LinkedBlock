#pragma once
#include "SceneClass.h"
#include "StageButton.h"
class SelectScene :
	public SceneClass
{
public:
	SelectScene();
	~SelectScene();

	virtual void	Release();
	virtual int		Start();
	virtual int		Update();
	virtual int		OnEvent(Event&);

private:
	GameObject* m_titleImg;
	CircleEffect* clippingEffect;
	StageButton** m_stageBtn;

	bool m_changing;
	bool m_escape;
};

