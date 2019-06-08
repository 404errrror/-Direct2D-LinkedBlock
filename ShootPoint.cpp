#include "stdafx.h"
#include "ShootPoint.h"


ShootPoint::ShootPoint()
{
}


ShootPoint::~ShootPoint()
{
}


void ShootPoint::Initialize()
{
	GameObject::Initialize();
	m_pComponentHub->AddComponent(ComponentHub::IMAGE);
	m_pComponentHub->m_pImage->SetImage(g_hasher("ShootPoint_Default"));
	//m_isUi = true;
}

void ShootPoint::Release()
{
	GameObject::Release();
	delete this;
}


int ShootPoint::Start()
{
	m_pComponentHub->m_pImage->SetBottom(-1000);
	return 0;
}


int ShootPoint::Update()
{

	Vector2 postion =  Camera::GetCameraPos() + g_mouseDesPos;

	m_pComponentHub->m_pTransform->SetPosition(postion);
	return 0;
}


int ShootPoint::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}