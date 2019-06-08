#pragma once
#include "ComponentHub.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Initialize();
	virtual void Release();

	virtual int Start() { return 0; };
	virtual int Update() { return 0; };
	virtual int OnEvent(Event&);
	virtual void OnCollision(GameObject* gameobject) {};

	void			SetId			(std::string);
	void			SetActive		(bool);
	void			SetRelease		(bool);
	void			SetMask			(bool);
	void			SetUi			(bool);
	// ������Ʈ ������Ʈ�� ����� ����Ÿ���� �����մϴ�.
	static void		SetRenderTarget	(ID2D1BitmapRenderTarget*);
	// ����ũ ����
	static void		SetMaskRender	(ID2D1BitmapRenderTarget*);
	// UI ����
	static void		SetUiRender		(ID2D1BitmapRenderTarget*);
	
	// �� �� �ҹ��ڷ� �س�������... ���߿� �ٲٱ�
	bool						isRelease() const;
	bool						isActive()	const;
	bool						IsMask()	const;
	bool						IsUi()		const;
	size_t						GetId			() const;
	std::string					GetName			() const;
	ComponentHub*				GetComponentHub	() const;
	static ID2D1BitmapRenderTarget*	GetRenderTarget	();
	static ID2D1BitmapRenderTarget* GetMask();
	static ID2D1BitmapRenderTarget* GetUiRenderTarget();
	static std::list<GameObject*> list;

protected:
	static ID2D1BitmapRenderTarget* m_pRenderTarget;
	static ID2D1BitmapRenderTarget* m_pUiRenderTarget;
	static ID2D1BitmapRenderTarget* m_pMask;

	bool			m_active;
	bool			m_release;
	bool			m_isMask;
	bool			m_isUi;
	std::string		m_name;
	size_t			m_idHash;
	ComponentHub*	m_pComponentHub;
};