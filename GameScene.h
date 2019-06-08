#pragma once
#include "SceneClass.h"
#include "GameBackground.h"
#include "GunSystem.h"
#include "FireWood.h"
#include "Character.h"
#include "EnemySystem.h"
class GameScene :
	public SceneClass
{
public:
	GameScene();
	~GameScene();

	virtual void	Release();
	virtual int		Start();
	virtual int		Update();
	virtual int		OnEvent(Event&);

	static bool Reatart;

private:
	GameBackground* m_pBackground;
	CameraTarget* m_pCameraTarget;
	GunSystem* m_pGunSystem;
	FireWood* m_pFireWood;
	Character* m_pCharacter;
	EnemySystem* m_pEnemySystem;
};

