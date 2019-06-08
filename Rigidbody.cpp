#include "stdafx.h"
#include "Rigidbody.h"

std::list<Rigidbody*> Rigidbody::list;

Rigidbody::Rigidbody()
{
	list.push_back(this);
	m_mass = 0;
}


Rigidbody::~Rigidbody()
{
}


void Rigidbody::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);

	m_pBoxCollider = m_pGameObject->GetComponentHub()->m_pBoxCollider;
	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;
	if (m_pBoxCollider == nullptr)
	{
		CString errorLog;
		errorLog += m_pGameObject->GetName().c_str();
		MessageBox(
			g_hwnd,
			L"Rigidbody::Initialize\n게임오브젝트에 콜라이더가 없어서 충돌 체크를 할 수 없습니다.", 
			errorLog,
			MB_ICONERROR
			);
	}

	m_mass = 1;

}


void Rigidbody::Release()
{
	Component::Release();
	for (std::list<Rigidbody*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}


int Rigidbody::Start()
{
	return 0;
}

int Rigidbody::Update()
{
	if (m_pGameObject->isActive() == false || m_enable == false)
		return 0;

	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
	{
		if (m_pBoxCollider == *it)
			continue;

		if (m_pBoxCollider->DetectCollision(*it))
			Collision((*it));
	}

	return 0;
}

int Rigidbody::OnEvent(Event& event)
{
	return -1;
}


void Rigidbody::SetMass(float mass)
{
	if (mass < -1)
		mass = -1;
	m_mass = mass;
}


float Rigidbody::GetMass()
{
	return m_mass;
}


void Rigidbody::Collision(BoxCollider* coll)
{
	if (coll->IsEnable() == false)
		return;

	if (!m_pBoxCollider->IsTrigger() && !coll->IsTrigger())
	{
		D2D1_RECT_F myRect = m_pBoxCollider->GetRange();
		D2D1_RECT_F collRect = coll->GetRange();
		Vector2 collCenter = Vector2((collRect.left + collRect.right) * 0.5, (collRect.top + collRect.bottom) * 0.5);

		float collMass = coll->GetMass();
		float myMassNormal, collMassNormal;

		float leftDistance = myRect.left - collRect.right;
		float topDistance = collRect.bottom - myRect.top;
		float rightDistance = collRect.left - myRect.right;
		float bottomDistance = myRect.bottom - collRect.top;



		// Mass 비율 설정
		if (m_mass == -1)
		{
			return;
		}
		else if (collMass != -1)
		{
			collMassNormal = collMass / (m_mass + collMass);
			myMassNormal = m_mass / (m_mass + collMass);
		}
		else
		{
			myMassNormal = 0;
			collMassNormal = 1;
		}


		// 왼쪽 체크
		if (
			leftDistance > topDistance &&
			leftDistance > rightDistance &&
			leftDistance > bottomDistance
			)
		{
			// 기본적으로 음수이므로.
			leftDistance *= -1;

			// 부딪힐 때 튕겨나가는 기능?. 부딪힌 오브젝트의 Mass의 비율만큼 이 오브젝트가 튕겨나가져야함.
			// 부딪힌 오브젝트의 Mass가 엄청 크면 이 오브젝트가 많이 튕겨나가져야하기 때문.
			m_pTransform->Translate(Vector2(1, 0) * leftDistance * collMassNormal);

			// 부딪힌 오브젝트의 튕김은 이 오브젝트의 Mass 비율
			//굳이 안해줘도 되지만 부딪힌 오브젝트가 다시 콜라이더 연산을 하게 되므로.
			coll->m_pTransfrom->Translate(Vector2(-1, 0) * leftDistance * myMassNormal);

		}

		// 오른쪽 체크
		if (
			rightDistance > topDistance &&
			rightDistance > leftDistance &&
			rightDistance > bottomDistance
			)
		{
				rightDistance *= -1;
				m_pTransform->Translate(Vector2(-1, 0) * rightDistance * collMassNormal);
				coll->m_pTransfrom->Translate(Vector2(1, 0) * rightDistance * myMassNormal);
		}

		// 윗쪽 체크
		if (
			topDistance > leftDistance &&
			topDistance > rightDistance &&
			topDistance > bottomDistance
			)
		{
			topDistance *= -1;
			m_pTransform->Translate(Vector2(0, -1) * topDistance * collMassNormal);
			coll->m_pTransfrom->Translate(Vector2(0, 1) * topDistance * myMassNormal);
		}

		// 아랫쪽 체크
		if (
			bottomDistance > leftDistance &&
			bottomDistance > rightDistance &&
			bottomDistance > topDistance
			)
		{
			bottomDistance *= -1;
			m_pTransform->Translate(Vector2(0, 1) * bottomDistance * collMassNormal);
			coll->m_pTransfrom->Translate(Vector2(0, -1) * bottomDistance * myMassNormal);
		}

		// 다하고 콜라이더 업뎃.
		m_pBoxCollider->Update();
		coll->Update();
	}

	// 이벤트 전송
	coll->OnEvent(CollisionEvent(m_pGameObject));

	m_pGameObject->OnEvent(CollisionEvent(coll->m_pTransfrom->GetGameobject()));


	return;
}