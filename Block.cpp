#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
{
}


CBlock::~CBlock()
{
}


void CBlock::Initialize()
{
	GameObject::Initialize();

	SetId("Block");
	m_pComponentHub->AddComponent(ComponentHub::RECT_RENDER);
	m_pComponentHub->AddComponent(ComponentHub::BOX_COLLIDER);

}


void CBlock::Release()
{
	GameObject::Release();
}


int CBlock::Start()
{
	m_pComponentHub->m_pRectRender->AlignCollider();
	m_pComponentHub->m_pRectRender->SetStrokeWidth(5);
	return 0;
}


int CBlock::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}