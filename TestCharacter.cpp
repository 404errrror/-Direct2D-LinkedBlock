#include "stdafx.h"
#include "TestCharacter.h"


TestCharacter::TestCharacter()
{
	speed = 0;
	key = 0;
}


TestCharacter::~TestCharacter()
{
}


void TestCharacter::Initialize()
{
	GameObject::Initialize();
	SetId("TestCharacter");
	m_pComponentHub->AddComponent(ComponentHub::Type::IMAGE);
	m_pComponentHub->AddComponent(ComponentHub::Type::FRAME_ANIMATION);
	m_pComponentHub->AddComponent(ComponentHub::Type::BOX_COLLIDER);
	m_pComponentHub->AddComponent(ComponentHub::Type::RIGIDBODY);
	m_pComponentHub->AddComponent(ComponentHub::Type::RECT_RENDER);
	m_pComponentHub->AddComponent(ComponentHub::Type::CIRCLE_RENDER);
	Start();
}


void TestCharacter::Release()
{
	GameObject::Release();

	delete this;
}


int TestCharacter::Start()
{
	m_pComponentHub->m_pImage->SetImage(g_hasher("MyCharacterImgIdle0"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("MyCharacterImgIdle0"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("MyCharacterImgIdle1"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun1"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun2"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun3"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun4"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun5"));
	m_pComponentHub->m_pFrameAnimation->AddImage(g_hasher("Run"), g_hasher("MyCharacterImgRun0"));
	
	m_pComponentHub->m_pFrameAnimation->SetState("Idle");
	m_pComponentHub->m_pTransform->SetPosition(Vector2(0, 0));
	m_pComponentHub->m_pTransform->SetScale(Vector2(1, 1));

	speed = 10;
	key = 1;
	return 0;
}


int TestCharacter::Update()
{

	static int tempR = 0;
	tempR++;
	if (key == 1)
	{

		MoveFunc();
	}
	else
		MoveFunc2();
	return 0;
}


int TestCharacter::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	return -1;
}



void TestCharacter::MoveFunc()
{
	if (g_pInput->isKeyDown('W'))
	{
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
			m_pComponentHub->m_pTransform->GetPosition().x,
			m_pComponentHub->m_pTransform->GetPosition().y + speed * Time::GetDeltaTime() * 30
			)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
	}

	if (g_pInput->isKeyDown('S'))
	{
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
			m_pComponentHub->m_pTransform->GetPosition().x,
			m_pComponentHub->m_pTransform->GetPosition().y - speed * Time::GetDeltaTime() * 30
			)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
	}

	if (g_pInput->isKeyDown('D'))
	{
		m_pComponentHub->m_pTransform->SetFippping(false);
		m_pComponentHub->m_pTransform->SetRotation(15);		////////////// --------------------------> 나중에 지우기
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
			m_pComponentHub->m_pTransform->GetPosition().x + speed * Time::GetDeltaTime() * 30,
			m_pComponentHub->m_pTransform->GetPosition().y
			)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
		{
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
			if (m_pComponentHub->m_pTransform->GetScale().x < 0)
				m_pComponentHub->m_pTransform->SetScale(Vector2(
				m_pComponentHub->m_pTransform->GetScale().x * -1,
				m_pComponentHub->m_pTransform->GetScale().y
				));
		}
	}
	
	if (g_pInput->isKeyDown('A'))
	{
		m_pComponentHub->m_pTransform->SetFippping(true);
		m_pComponentHub->m_pTransform->SetRotation(-15);		////////////// --------------------------> 나중에 지우기
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
			m_pComponentHub->m_pTransform->GetPosition().x - speed * Time::GetDeltaTime() * 30,
			m_pComponentHub->m_pTransform->GetPosition().y
			)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
		{
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
			if (m_pComponentHub->m_pTransform->GetScale().x > 0)
				m_pComponentHub->m_pTransform->SetScale(Vector2(
				m_pComponentHub->m_pTransform->GetScale().x * -1,
				m_pComponentHub->m_pTransform->GetScale().y
				));

		}
	}

	

	// 아무키도 안눌렀을 때
	if (
		!(g_pInput->isKeyDown('W') ||
		g_pInput->isKeyDown('S') ||
		g_pInput->isKeyDown('D') ||
		g_pInput->isKeyDown('A')
		))
	{
		m_pComponentHub->m_pTransform->SetRotation(0);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Idle"))
			m_pComponentHub->m_pFrameAnimation->SetState("Idle");
	}
}


void TestCharacter::MoveFunc2()
{
	if (g_pInput->isKeyDown('I'))
	{
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
				m_pComponentHub->m_pTransform->GetPosition().x,
				m_pComponentHub->m_pTransform->GetPosition().y + speed * Time::GetDeltaTime() * 30
				)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
	}

	if (g_pInput->isKeyDown('K'))
	{
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
				m_pComponentHub->m_pTransform->GetPosition().x,
				m_pComponentHub->m_pTransform->GetPosition().y - speed * Time::GetDeltaTime() * 30
				)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
	}

	if (g_pInput->isKeyDown('L'))
	{
		m_pComponentHub->m_pTransform->SetFippping(false);
		m_pComponentHub->m_pTransform->SetRotation(15);		////////////// --------------------------> 나중에 지우기
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
				m_pComponentHub->m_pTransform->GetPosition().x + speed * Time::GetDeltaTime() * 30,
				m_pComponentHub->m_pTransform->GetPosition().y
				)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
		{
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
			if (m_pComponentHub->m_pTransform->GetScale().x < 0)
					m_pComponentHub->m_pTransform->SetScale(Vector2(
						m_pComponentHub->m_pTransform->GetScale().x * -1,
						m_pComponentHub->m_pTransform->GetScale().y
					));
		}
	}

	if (g_pInput->isKeyDown('J'))
	{
		m_pComponentHub->m_pTransform->SetFippping(true);
		m_pComponentHub->m_pTransform->SetRotation(-15);		////////////// --------------------------> 나중에 지우기
		m_pComponentHub->m_pTransform->SetPosition(
			Vector2(
				m_pComponentHub->m_pTransform->GetPosition().x - speed * Time::GetDeltaTime() * 30,
				m_pComponentHub->m_pTransform->GetPosition().y
				)
			);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Run"))
		{
			m_pComponentHub->m_pFrameAnimation->SetState(g_hasher("Run"));
			if (m_pComponentHub->m_pTransform->GetScale().x > 0)
				m_pComponentHub->m_pTransform->SetScale(Vector2(
				m_pComponentHub->m_pTransform->GetScale().x * -1,
				m_pComponentHub->m_pTransform->GetScale().y
				));

		}
	}



	// 아무키도 안눌렀을 때
	if (
		!(g_pInput->isKeyDown('I') ||
			g_pInput->isKeyDown('K') ||
			g_pInput->isKeyDown('J') ||
			g_pInput->isKeyDown('L')
			))
	{
		m_pComponentHub->m_pTransform->SetRotation(0);
		if (m_pComponentHub->m_pFrameAnimation->GetState() != g_hasher("Idle"))
			m_pComponentHub->m_pFrameAnimation->SetState("Idle");
	}
}