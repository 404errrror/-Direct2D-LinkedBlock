#include "stdafx.h"
#include "WallBlock.h"


WallBlock::WallBlock()
{
}


WallBlock::~WallBlock()
{
}


void WallBlock::Initialize()
{
	CBlock::Initialize();

	SetId("WallBlock");
}


void WallBlock::Release()
{
	CBlock::Release();
	delete this;
}


int WallBlock::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pRectRender->SetColor(D2D1::ColorF(0.3, 0.3, 0.3));
	return 0;
}


int WallBlock::Update()
{
	return 0;
}


int WallBlock::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	return -1;
}