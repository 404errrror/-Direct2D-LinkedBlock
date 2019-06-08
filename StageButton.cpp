#include "stdafx.h"
#include "StageButton.h"
#include "StageSelector.h"


StageButton::StageButton()
{
	m_stage = 0;
	m_totalTime = 0;
	m_aniEnd = false;
	m_clicked = false;
	m_width = 0;
	m_height = 0;
}


StageButton::~StageButton()
{
}


void StageButton::Initialize()
{
	GameObject::Initialize();
	SetId("Button");

	m_pComponentHub->AddComponent(ComponentHub::BUTTON);
	m_pComponentHub->AddComponent(ComponentHub::SHAPE_ANIMATION);
	Start();
}


void StageButton::Release()
{
	GameObject::Release();
	delete this;
}


int StageButton::Start()
{
	char fileName[64];
	sprintf_s(fileName, "Stage%dBtn_Idle",m_stage);
	m_pComponentHub->m_pButton->SetImage(g_hasher(fileName));
	sprintf_s(fileName, "Stage%dBtn_Focus", m_stage);
	m_pComponentHub->m_pButton->SetFucusImage(g_hasher(fileName));
	sprintf_s(fileName, "Stage%dBtn_Press", m_stage);
	m_pComponentHub->m_pButton->SetDownImage(g_hasher(fileName));

	m_pComponentHub->m_pShapeAnimation->SetScale(Vector2(0, 0), Vector2(1, 1));
	m_pComponentHub->m_pShapeAnimation->SetTime(0.5);
	m_pComponentHub->m_pShapeAnimation->SetAnimationType(ShapeAnimation::ANIMATION_SMOOTH_END);

	m_pComponentHub->m_pTransform->SetScale(Vector2(0, 0));

	m_width = m_pComponentHub->m_pImage->GetImageWidth();
	m_height = m_pComponentHub->m_pImage->GetImageHeight();
	return 0;
}


int StageButton::Update()
{
	m_totalTime += Time::GetDeltaTime();

	// 처음에 이미지 사이즈 받아서 콜라이더 만드는 함수가 Start()에 있음
	// 그런데 처음에 스케일을 0으로 줘버리는 바람에 콜라이더가 감지가 안됬음. 그래서 매 프레임 콜라이더 크기 조정.
	AlignCollider();

	if (m_totalTime > m_stage * 0.15 && m_aniEnd == false)
	{
		m_aniEnd = true;
		m_pComponentHub->m_pShapeAnimation->Play();
	}
	return 0;
}


int StageButton::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	switch (event.GetType())
	{
	case Event::Type::BUTTON_CLICK:
		StageSelector::SetStage(m_stage);
		m_clicked = true;
		return 0;
	default:
		break;
	}
	return -1;
}


void StageButton::SetStage(int stageNum)
{
	m_stage = stageNum;
}


void StageButton::AlignCollider()
{
	m_pComponentHub->m_pBoxCollider->SetRange(
		m_width * m_pComponentHub->m_pTransform->GetScale().x,
		m_height * m_pComponentHub->m_pTransform->GetScale().y
		);
}