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
	// �ּҸ� �޾ƿ����Ƿ� delete�ϸ� �ȵ�.
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