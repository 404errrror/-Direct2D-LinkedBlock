#include "stdafx.h"
#include "Slime.h"


Slime::Slime()
{
	m_pTransform = nullptr;
	m_pFrameAnimation = nullptr;
	m_hp = 10;
	m_attack = 2;
	m_speed = 200;
	m_hittedAniTime = 0.5;
	m_isDie = false;
	m_moveAble = true;
	m_isAttacking = false;
	m_attackTime = 0;
}


Slime::~Slime()
{
}


void Slime::Initialize()
{
	GameObject::Initialize();
	m_pTransform = m_pComponentHub->m_pTransform;
	SetId("SlimeObject");

	m_pComponentHub->AddComponent(ComponentHub::BOX_COLLIDER);
	m_pComponentHub->AddComponent(ComponentHub::RIGIDBODY);

	m_pComponentHub->AddComponent(ComponentHub::IMAGE);
	m_pComponentHub->m_pImage->SetImage(g_hasher("Slime"));

	m_pComponentHub->AddComponent(ComponentHub::FRAME_ANIMATION);
	m_pFrameAnimation = m_pComponentHub->m_pFrameAnimation;
	m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Slime"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@1"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@2"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@3"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@4"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@5"));
	m_pFrameAnimation->AddImage(g_hasher("Move"), g_hasher("Slime_Move@6"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@1"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@2"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@3"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@4"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@5"));
	m_pFrameAnimation->AddImage(g_hasher("Attack"), g_hasher("Slime_Attack@6"));
	m_pFrameAnimation->AddImage(g_hasher("Hitted"), g_hasher("Slime_Hitted@1"));
	m_pFrameAnimation->AddImage(g_hasher("Die"), g_hasher("Slime_Die@1"));
}


void Slime::Release()
{
	GameObject::Release();
	delete this;
}


int Slime::Start()
{

	m_pFrameAnimation->SetState("Move");
	m_pComponentHub->m_pBoxCollider->SetTrigger(true);
	m_pComponentHub->m_pImage->SetBottom(-64);

	m_pComponentHub->m_pBoxCollider->SetRange(
		m_pComponentHub->m_pImage->GetImageWidth() * 0.5 * m_pComponentHub->m_pTransform->GetScale().x
		, m_pComponentHub->m_pImage->GetImageWidth() * 0.5 * m_pComponentHub->m_pTransform->GetScale().y
		);

	return 0;
}


int Slime::Update()
{
	if (m_active == false)
		return 0;

	// 죽었을 때
	if (m_isDie)
	{
		Die();
		return 0;
	}

	// 피격 애니메이션 시간 체크.
	if (m_pFrameAnimation->GetState() == g_hasher("Hitted"))
	{
		m_hittedAniTime += Time::GetDeltaTime();
	}



	// 피격 당하고 원래대로 돌아갈 때
	if (m_hittedAniTime > 0.5 && m_isDie == false)
	{
		m_hittedAniTime = 0;
		m_attackTime = 0;
		m_isAttacking = false;
		m_pFrameAnimation->SetState("Move");
		m_moveAble = true;
	}

	// 캐릭터와 가까이 있을 때
	///////////// Idle일때 피격시 이상함.
	if (Vector2::GetDistance(m_pTransform->GetPosition(), Vector2(0, 0)) <= 100 && m_pFrameAnimation->GetState() != g_hasher("Hitted"))
	{
		if (m_moveAble)
		{
			m_pFrameAnimation->SetState("Idle");
			m_moveAble = false;
		}
		if (m_isAttacking == false)
			Attack();
	}

	// 플레이어를 향해 움직이기
	if (m_moveAble)
		m_pComponentHub->m_pTransform->Translate(
		Vector2::Normalize(m_pTransform->GetPosition() * -1) * Time::GetDeltaTime() * m_speed
		);


	// 어택 딜레이
	if (m_isAttacking && m_isDie == false)
		m_attackTime += Time::GetDeltaTime();



	if (m_attackTime > 1.5 )
	{
		m_attackTime = 0;
		Attack();
	}






	return 0;
}


int Slime::OnEvent(Event& event)
{
	GameObject::OnEvent(event);
	switch (event.GetType())
	{
	case Event::ATTACK:
		Hitted(*(int*)event.GetInfo());
		return 0;
	case Event::SYSTEM_RESIZE:
		m_pComponentHub->m_pBoxCollider->SetRange(
			256 * 0.5 * m_pComponentHub->m_pTransform->GetScale().x
			, 256 * 0.5 * m_pComponentHub->m_pTransform->GetScale().y
			);
		return 0;
	default:
		return -1;
	}


}


void Slime::Attack()
{
	m_isAttacking = true;
	m_pFrameAnimation->SetState("Attack");
	m_pFrameAnimation->SetReplay(false);
	m_pFrameAnimation->Play();

	Character::m_hp -= m_attack;
}


void Slime::Die()
{

	m_pComponentHub->m_pImage->SetOpacity(
		m_pComponentHub->m_pImage->GetOpacity() - Time::GetDeltaTime() * 0.5
		);
	if (m_pComponentHub->m_pImage->GetOpacity() < 0)
		m_active = false;
}


void Slime::Hitted(int attack)
{
	if (m_isDie)
		return;

	m_hittedAniTime = 0;
	m_hp -= attack;
	m_moveAble = false;
	m_isAttacking = false;

	if (m_hp <= 0)
	{
		m_pFrameAnimation->Stop();
		m_pFrameAnimation->SetReplay(true);
		m_pFrameAnimation->SetState("Die");
		m_pFrameAnimation->Play();
		m_isDie = true;
	}
	else
	{
		m_pFrameAnimation->Stop();
		m_pFrameAnimation->SetState("Hitted");
		m_pFrameAnimation->SetReplay(true);
		m_pFrameAnimation->Play();
	}

}


void Slime::Respawn(Vector2 position)
{
	m_pTransform->SetPosition(position);
	m_pComponentHub->m_pImage->SetOpacity(1);

	m_pTransform->SetScale(Vector2(1, 1));
	m_pComponentHub->m_pBoxCollider->SetRange(
		m_pComponentHub->m_pImage->GetImageWidth() * 0.5 * m_pComponentHub->m_pTransform->GetScale().x
		, m_pComponentHub->m_pImage->GetImageWidth() * 0.5 * m_pComponentHub->m_pTransform->GetScale().y
		);

	m_hp = 10;
	m_isDie = false;
	m_moveAble = true;
	m_hittedAniTime = 0;
	m_pFrameAnimation->SetState("Move");

	if (m_pTransform->GetPosition().x > 0)
		m_pTransform->SetScale(Vector2(-1, 1));


	m_active = true;
}