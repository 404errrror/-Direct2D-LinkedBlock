#pragma once
#include "GameObject.h"
#include "MyCharacter.h"
class CameraTarget :
	public GameObject
{
public:
	CameraTarget();
	~CameraTarget();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	// MyCharacter블럭을 하나 찾아서 타겟으로 설정합니다.
	void RefreshTarget();
	// 카메라를 다음 MyCharacter블럭으로 변경합니다.
	void ChangeNextTarget();
private:
	Transform* m_pNowTarget;
	Transform* m_pTransform;
	float mouseSencivity;
	float m_keyDelay;
};

