#include "stdafx.h"
#include "GameObject.h"

ID2D1BitmapRenderTarget* GameObject::m_pRenderTarget;
ID2D1BitmapRenderTarget* GameObject::m_pUiRenderTarget;
ID2D1BitmapRenderTarget* GameObject::m_pMask;
std::list<GameObject*> GameObject::list;
GameObject::GameObject()
{
	list.push_back(this);

	m_active = true;
	m_release = false;
	m_isMask = false;
	m_isUi = false;
	m_name = "";
	m_idHash = 0;
	m_pComponentHub = nullptr;
}


GameObject::~GameObject()
{
}


void GameObject::Initialize()
{

	m_pComponentHub = new ComponentHub;
	m_pComponentHub->Initialzie(this);

	// 위치값은 어떠한 게임오브젝트라도 가지고 있어야함.
	m_pComponentHub->AddComponent(ComponentHub::Type::TRANSFORM);
}


void GameObject::Release()
{
	RELEASE(m_pComponentHub);

	for (std::list<GameObject*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}

}


int GameObject::OnEvent(Event& event)
{
	switch (event.GetType())
	{

	case Event::Type::SYSTEM_RESIZE:
		m_pComponentHub->SendEvent(ComponentHub::ALL,event);
		return 0;

	case Event::Type::COLLISION:
		OnCollision((GameObject*)event.GetInfo());
		return 0;
	default:
		return -1;
	}
}


void GameObject::SetId(std::string str)
{
	m_name = str;
	m_idHash = g_hasher(str);
}


void GameObject::SetActive(bool active)
{
	m_active = active;
}


void GameObject::SetRelease(bool isRelease)
{
	m_release = isRelease;
}


void GameObject::SetMask(bool isMask)
{
	m_isMask = isMask;
}


void GameObject::SetUi(bool isUi)
{
	m_isUi = isUi;
}


void GameObject::SetRenderTarget(ID2D1BitmapRenderTarget* bitmapRenderTarget)
{
	m_pRenderTarget = bitmapRenderTarget;
}


void GameObject::SetMaskRender(ID2D1BitmapRenderTarget* bitmapRenderTarget)
{
	m_pMask = bitmapRenderTarget;
}


void GameObject::SetUiRender(ID2D1BitmapRenderTarget* bitmapRenderTarget)
{
	m_pUiRenderTarget = bitmapRenderTarget;
}


bool GameObject::isRelease() const
{
	return m_release;
}


bool GameObject::isActive() const
{
	return m_active;
}


bool GameObject::IsMask() const
{
	return m_isMask;
}


bool GameObject::IsUi() const
{
	return m_isUi;
}


size_t GameObject::GetId() const
{
	return m_idHash;
}


std::string GameObject::GetName() const
{
	return m_name;
}


ComponentHub* GameObject::GetComponentHub() const
{
	return m_pComponentHub;
}


ID2D1BitmapRenderTarget* GameObject::GetRenderTarget()
{
	return m_pRenderTarget;
}


ID2D1BitmapRenderTarget* GameObject::GetMask()
{
	return m_pMask;
}


ID2D1BitmapRenderTarget* GameObject::GetUiRenderTarget()
{
	return m_pUiRenderTarget;
}