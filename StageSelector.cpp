#include "stdafx.h"
#include "StageSelector.h"

int StageSelector::m_stage;

StageSelector::StageSelector()
{
}


StageSelector::~StageSelector()
{
}


void StageSelector::SetStage(int stage)
{
	m_stage = stage;
}


int StageSelector::GetStage()
{
	return m_stage;
}