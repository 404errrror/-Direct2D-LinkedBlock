#pragma once
#include "SceneClass.h"
#include "StartButton.h"
class StartScene :
	public SceneClass
{
public:
	StartScene();
	~StartScene();

	virtual void	Release();
	virtual int		Start();
	virtual int		Update();
	virtual int		OnEvent(Event&);

private:
	GameObject* titleImage;
	GameObject* backgroundRect;
	StartButton* startBtn;
	CircleEffect* clippingEffect;
	GameObject*	cameraTarget;

	bool m_changing;
};

