#include "stdafx.h"
#include "FireWood.h"


FireWood::FireWood()
{
	m_pLight = nullptr;
	lightPercent = 1;
}


FireWood::~FireWood()
{
}


void FireWood::Initialize()
{
	GameObject::Initialize();
	m_pComponentHub->AddComponent(ComponentHub::IMAGE);

	m_pLight = new Light();
	m_pLight->Initialize();
}


void FireWood::Release()
{
	GameObject::Release();
	RELEASE(m_pLight);
	delete this;
}


int FireWood::Start()
{
	m_pComponentHub->m_pImage->SetImage(g_hasher("FireWood"));
	m_pComponentHub->m_pTransform->SetPosition(Vector2(0, -200));

	m_pLight->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	return 0;
}


int FireWood::Update()
{
	return 0;
}


int FireWood::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}