#pragma once
#include "GameObject.h"
#include "DefaultGun.h"
#include "ShootPoint.h"
#include "GameRestartBtn.h"
class GunSystem :
	public GameObject, public ShootInterface
{
public:
	GunSystem();
	~GunSystem();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	virtual int Shoot();
	virtual int Reload();

private:

	enum InfoType
	{
		NONE,
		RELOAD,
		LACK_BULLET,
		GAME_OVER				// 얘 다른 곳으로 분리.
	};

	void RefreshText();
	void ChagneGun();
	void ShowLackBulletText();
	void InfoEndCheck();
	void ShowGameOverText();

	Vector2 m_screenSize;
	ShootPoint* m_pShootPoint;
	GameObject* m_pCountText;
	char m_charBuffer[32];		//----------> 나중에 텍스트 클래스로 분리
	GameObject* m_pInfoText;	//----------> 애도  InfoText로 분리.
	GameRestartBtn* m_pRestartBtn;

	// Gun Data
	GunInterface* m_pGunPtr;
	DefaultGun m_defaultGun;
	
	bool m_shootLock;
	bool m_reloadDown;
	bool m_showInfoText;
	float m_reloadTime;
	float m_infoTextTime;
	InfoType m_infoType;
};

