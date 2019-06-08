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
	// 컴포넌트 업데이트시 사용할 렌더타겟을 설정합니다.
	static void		SetRenderTarget	(ID2D1BitmapRenderTarget*);
	// 마스크 설정
	static void		SetMaskRender	(ID2D1BitmapRenderTarget*);
	// UI 설정
	static void		SetUiRender		(ID2D1BitmapRenderTarget*);
	
	// 왜 다 소문자로 해놓았을까... 나중에 바꾸기
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