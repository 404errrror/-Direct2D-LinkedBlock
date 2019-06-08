#pragma once
#include "CircleEffect.h"
#include "MapCreator.h"
#include "CameraTarget.h"
#include "ClearSelectButton.h"
#include "BackgroundParticle.h"

class GameTestScene : public SceneClass
{
public:
	GameTestScene();
	~GameTestScene();

	virtual void	Release();
	virtual int		Start();
	virtual int		Update();
	virtual int		OnEvent(Event&);

private:
	bool ClearCheck();

	//MyCharacter* myCharacter;
	//MyCharacter* myCharacter2;
	//DestBlock** destBlockArr;

	CircleEffect* m_pTestEffect;
	MapCreator* m_pMapCreator;
	CameraTarget* m_pCamTarget;
	GameObject* m_pClearImage;
	ClearSelectButton* m_pSelectBtn;
	BackgroundParticle* m_pBackground;

	bool m_changing;
	bool m_rDowned;
	bool m_isClear;
	bool m_selectClicked;
};

