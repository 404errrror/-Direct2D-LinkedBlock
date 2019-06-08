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

	// MyCharacter���� �ϳ� ã�Ƽ� Ÿ������ �����մϴ�.
	void RefreshTarget();
	// ī�޶� ���� MyCharacter������ �����մϴ�.
	void ChangeNextTarget();
private:
	Transform* m_pNowTarget;
	Transform* m_pTransform;
	float mouseSencivity;
	float m_keyDelay;
};

