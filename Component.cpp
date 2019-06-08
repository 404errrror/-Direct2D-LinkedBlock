#include "stdafx.h"
#include "Component.h"

Component::Component()
{

	m_enable = true;
	m_pGameObject = nullptr;
}


Component::~Component()
{
}


void Component::Initialize(GameObject* gameObject)
{
	m_pGameObject = gameObject;
}

void Component::Release()
{
	// 주소만 받아왔으므로 delete하면 안됨.
	m_pGameObject = nullptr;
}


void Component::SetEnable(bool enable)
{
	m_enable = enable;
}


bool Component::IsEnable()
{
	return m_enable;
}