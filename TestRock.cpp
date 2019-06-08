#include "stdafx.h"
#include "TestRock.h"


TestRock::TestRock()
{
}


TestRock::~TestRock()
{
}


void TestRock::Initialize()
{
	GameObject::Initialize();
	SetId("TestRock");
	m_pComponentHub->AddComponent(ComponentHub::Type::IMAGE);
	m_pComponentHub->AddComponent(ComponentHub::Type::BOX_COLLIDER);
	m_pComponentHub->AddComponent(ComponentHub::Type::RIGIDBODY);

	Start();
}


void TestRock::Release()
{
	GameObject::Release();
}


int TestRock::Start()
{
	m_pComponentHub->m_pImage->SetImage(g_hasher("TestRockImg"));
	m_pComponentHub->m_pRigidbody->SetMass(5);
	return 0;
}


int TestRock::Update()
{
	return 0;
}


int TestRock::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	return -1;
}