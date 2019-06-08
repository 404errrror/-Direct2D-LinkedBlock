#include "stdafx.h"
#include "DieBlock.h"


DieBlock::DieBlock()
{
}


DieBlock::~DieBlock()
{
}


void DieBlock::Initialize()
{
	CBlock::Initialize();
	SetId("DieBlock");

	m_pRotateEffect = new RectRotateEffect();
	m_pRotateEffect->Initialize();
}


void DieBlock::Release()
{
	CBlock::Release();

	m_pRotateEffect->Release();

	delete this;
}


int DieBlock::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pTransform->SetScale(Vector2(1,1));
	m_pComponentHub->m_pRectRender->SetColor(D2D1::ColorF(1, 0.5, 0.5));

	m_pRotateEffect->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
	m_pRotateEffect->SetColor(D2D1::ColorF(1, 0.5, 0.5));
	m_pRotateEffect->SetType(RectRotateEffect::TYPE_DEFAULT);

	return 0;
}


int DieBlock::Update()
{

	return 0;
}


int DieBlock::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	return -1;
}


void DieBlock::OnCollision(GameObject* gameobject)
{
}