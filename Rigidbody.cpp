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
			L"Rigidbody::Initialize\n���ӿ�����Ʈ�� �ݶ��̴��� ��� �浹 üũ�� �� �� �����ϴ�.", 
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



		// Mass ���� ����
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


		// ���� üũ
		if (
			leftDistance > topDistance &&
			leftDistance > rightDistance &&
			leftDistance > bottomDistance
			)
		{
			// �⺻������ �����̹Ƿ�.
			leftDistance *= -1;

			// �ε��� �� ƨ�ܳ����� ���?. �ε��� ������Ʈ�� Mass�� ������ŭ �� ������Ʈ�� ƨ�ܳ���������.
			// �ε��� ������Ʈ�� Mass�� ��û ũ�� �� ������Ʈ�� ���� ƨ�ܳ��������ϱ� ����.
			m_pTransform->Translate(Vector2(1, 0) * leftDistance * collMassNormal);

			// �ε��� ������Ʈ�� ƨ���� �� ������Ʈ�� Mass ����
			//���� �����൵ ������ �ε��� ������Ʈ�� �ٽ� �ݶ��̴� ������ �ϰ� �ǹǷ�.
			coll->m_pTransfrom->Translate(Vector2(-1, 0) * leftDistance * myMassNormal);

		}

		// ������ üũ
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

		// ���� üũ
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

		// �Ʒ��� üũ
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

		// ���ϰ� �ݶ��̴� ����.
		m_pBoxCollider->Update();
		coll->Update();
	}

	// �̺�Ʈ ����
	coll->OnEvent(CollisionEvent(m_pGameObject));

	m_pGameObject->OnEvent(CollisionEvent(coll->m_pTransfrom->GetGameobject()));


	return;
}