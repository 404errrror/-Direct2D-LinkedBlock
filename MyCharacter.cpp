#include "stdafx.h"
#include "MyCharacter.h"

std::list<MyCharacter*> MyCharacter::list;

MyCharacter::MyCharacter()
{
	list.push_back(this);

	m_pTransform = nullptr;
	coreEffect = nullptr;
	m_pRotateEffect = nullptr;
	m_pDieEffect = nullptr;
	m_beforePos = Vector2(0, 0);
	isDie = false;
	moveEvent = false;
	startDelay = 0;
}


MyCharacter::~MyCharacter()
{
}


void MyCharacter::Initialize()
{
	CBlock::Initialize();
	SetId("MyCharacter");
	m_pComponentHub->AddComponent(ComponentHub::RIGIDBODY);
	m_pComponentHub->AddComponent(ComponentHub::MOTION_ANIMATION);
	m_pTransform = m_pComponentHub->m_pTransform;

	coreEffect = new GameObject();
	coreEffect->Initialize();
	coreEffect->GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);

	m_pRotateEffect = new RectRotateEffect();
	m_pRotateEffect->Initialize();

	m_pDieEffect = new ExplosionEffect();
	m_pDieEffect->Initialize();
	
}


void MyCharacter::Release()
{
	CBlock::Release();

	coreEffect->Release();
	delete coreEffect;

	m_pRotateEffect->Release();
	m_pDieEffect->Release();

	Camera::SetObject(nullptr);

	for (std::list<MyCharacter*>::iterator it = list.begin(); it != list.end(); ++it)
		if (*it == this)
		{
			list.erase(it);
			break;
		}

	delete this;
}


int MyCharacter::Start()
{
	CBlock::Start();
	m_pComponentHub->m_pRectRender->SetColor(D2D1::ColorF(0.5, 0.5, 0.5, 1));
	m_pComponentHub->m_pMotionAnimation->SetTime(0.2);
	m_pComponentHub->m_pBoxCollider->SetRange(
		m_pComponentHub->m_pRectRender->GetWidth() - 20,
		m_pComponentHub->m_pRectRender->GetHeight() - 20
		);

	coreEffect->GetComponentHub()->m_pRectRender->SetFill(true);
	coreEffect->GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(0.6, 0.6, 0.6, 1));

	coreEffect->GetComponentHub()->m_pTransform->SetScale(Vector2(0.2, 0.2));
	coreEffect->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);

	m_pDieEffect->SetParent(m_pTransform);
	m_pDieEffect->SetAmount(64);
	m_pDieEffect->SetSpeed(10);
	m_pDieEffect->SetColor(m_pComponentHub->m_pRectRender->GetColor());

	m_pRotateEffect->GetComponentHub()->m_pTransform->SetParent(m_pTransform);
	m_pRotateEffect->SetType(RectRotateEffect::TYPE_FADEOUT);
	m_pRotateEffect->SetColor(D2D1::ColorF(0.5, 0.5, 0.5, 1));

	m_beforePos = m_pTransform->GetPosition();
	return 0;
}


int MyCharacter::Update()
{
	startDelay += Time::GetDeltaTime();
	coreEffect->GetComponentHub()->m_pTransform->Rotate(3);

	if (isDie)
	{
		FadeOutCharacter();
		return 0;
	}

	if (m_pComponentHub->m_pMotionAnimation->IsPlay() == false && 
		startDelay > 0.5)
	{
		if (moveEvent)
		{

			MessageEvent myMoveEvent("Moved");
			// 포탈 블럭에게 전송.
			for (std::list<PotalBlock*>::iterator it = PotalBlock::list.begin(); it != PotalBlock::list.end(); ++it)
			{
				if ((*it)->isActive())
				{
					(*it)->OnEvent(myMoveEvent);
				}
			}
			// 도착 블럭에게 전송
			for (std::list<DestBlock*>::iterator it = DestBlock::list.begin(); it != DestBlock::list.end(); ++it)
			{
				if ((*it)->isActive())
				{
					(*it)->OnEvent(myMoveEvent);
				}
			}
			// 움직일 수 있는 블럭에게 전송
			for (std::list<MoveAbleBlock*>::iterator it = MoveAbleBlock::list.begin(); it != MoveAbleBlock::list.end(); ++it)
			{
				if ((*it)->isActive())
				{
					(*it)->OnEvent(myMoveEvent);
				}
			}

			myMoveEvent.Release();
			moveEvent = false;
			m_beforePos = m_pTransform->GetPosition();
		}

		AlignPos();
		MoveControl();
	}
	
	return 0;
}


int MyCharacter::OnEvent(Event& event)
{
	CBlock::OnEvent(event);
	switch (event.GetType())
	{
	default:
		break;
	}
	return -1;
}


void MyCharacter::OnCollision(GameObject* gameobject)
{
	if (gameobject->GetId() == g_hasher("DieBlock"))
	{
			Die();
	}
	if (gameobject->GetId() == g_hasher("WallBlock") || gameobject->GetId() == g_hasher("MyCharacter")
		)
	{
		m_pTransform->SetPosition(m_beforePos);
		AlignPos();
		//m_pComponentHub->m_pMotionAnimation->Stop();
		moveEvent = false;
	}
	if (gameobject->GetId() == g_hasher("MoveAbleBlock") &&
		gameobject->GetComponentHub()->m_pRigidbody->GetMass() == -1)
	{
		m_pTransform->SetPosition(m_beforePos);
		AlignPos();
		moveEvent = false;
	}
		
}


bool MyCharacter::IsMoveAble()
{
	// 애니메이션이 플레이 되고있지 않으면 움직일 수 있다는 것이므로 반전시켜준다.
	return !m_pComponentHub->m_pMotionAnimation->IsPlay();
}


void MyCharacter::MoveControl()
{

	if (g_pInput->isKeyDown('A'))
	{
		m_pComponentHub->m_pMotionAnimation->SetMove(m_pTransform->GetPosition(), m_pTransform->GetPosition() + Vector2(-100, 0));
	}
	
	if (g_pInput->isKeyDown('W'))
	{
		m_pComponentHub->m_pMotionAnimation->SetMove(m_pTransform->GetPosition(), m_pTransform->GetPosition() + Vector2(0, 100));
	}

	if (g_pInput->isKeyDown('D'))
	{
		m_pComponentHub->m_pMotionAnimation->SetMove(m_pTransform->GetPosition(), m_pTransform->GetPosition() + Vector2(100, 0));
	}

	if (g_pInput->isKeyDown('S'))
	{
		m_pComponentHub->m_pMotionAnimation->SetMove(m_pTransform->GetPosition(), m_pTransform->GetPosition() + Vector2(0, -100));
	}

	if (
		g_pInput->isKeyDown('A') ||
		g_pInput->isKeyDown('W') ||
		g_pInput->isKeyDown('D') ||
		g_pInput->isKeyDown('S'))
	{
		m_pComponentHub->m_pMotionAnimation->SetType(MotionAnimation::MOTION_ANIMATION_SMOOTH_START);
		m_pComponentHub->m_pMotionAnimation->Play();
		moveEvent = true;
	}
}

// 줄 맞추기?
void MyCharacter::AlignPos()
{
	Vector2 myPos = m_pComponentHub->m_pTransform->GetPosition();

	if (
		(int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth() > m_pComponentHub->m_pRectRender->GetWidth() * 0.5 ||
		(int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth() < m_pComponentHub->m_pRectRender->GetWidth() * 0.5 * -1
		)
	{
		if (myPos.x > 0)
			myPos.x = (int)myPos.x + m_pComponentHub->m_pRectRender->GetWidth() - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
		else
			myPos.x = (int)myPos.x - m_pComponentHub->m_pRectRender->GetWidth() - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
	}
	else
	{
		myPos.x = (int)myPos.x - (int)myPos.x % (int)m_pComponentHub->m_pRectRender->GetWidth();
	}

	if (
		(int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight() > m_pComponentHub->m_pRectRender->GetHeight() * 0.5 ||
		(int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight() < m_pComponentHub->m_pRectRender->GetHeight() * 0.5 * -1
		)
	{
		if (myPos.y > 0)
			myPos.y = (int)myPos.y + m_pComponentHub->m_pRectRender->GetHeight() - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
		else
			myPos.y = (int)myPos.y - m_pComponentHub->m_pRectRender->GetHeight() - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
	}
	else
	{
		myPos.y = (int)myPos.y - (int)myPos.y % (int)m_pComponentHub->m_pRectRender->GetHeight();
	}

	m_pComponentHub->m_pTransform->SetPosition(myPos);
}


void MyCharacter::Die()
{
	isDie = true;
	m_pComponentHub->m_pRigidbody->SetEnable(false);
	m_pComponentHub->m_pBoxCollider->SetEnable(false);
	m_pDieEffect->Play();
	m_pRotateEffect->FadeOut();
	//SetRelease(true);
}


void MyCharacter::FadeOutCharacter()
{
	m_pComponentHub->m_pRectRender->SetColor(
		D2D1::ColorF(
			m_pComponentHub->m_pRectRender->GetColor().r,
			m_pComponentHub->m_pRectRender->GetColor().g,
			m_pComponentHub->m_pRectRender->GetColor().b,
			m_pComponentHub->m_pRectRender->GetColor().a - Time::GetDeltaTime()
			)
		);

	coreEffect->GetComponentHub()->m_pRectRender->SetColor(
		m_pComponentHub->m_pRectRender->GetColor()
		);
}