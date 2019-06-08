#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
	m_position = Vector2(0, 0);
	m_scale = Vector2(1, 1);
	m_rotationZ = 0;
	m_flipping = false;
	m_pParent = nullptr;
}


Transform::~Transform()
{
}


void Transform::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	Start();
}


void Transform::Release()
{
	delete this;
}


int Transform::Start()
{
	return 0;
}


int Transform::Update()
{
	// -------------------> 나중에 카메라 연산하기.
	return 0;
}


int Transform::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	default:
		return -1;
	}
}


void Transform::SetPosition(Vector2& position)
{
	m_position = position;
	m_pGameObject->GetComponentHub()->SendEvent(ComponentHub::Type::ALL, Event(Event::Type::GAMEOBJECT_TRANSFORM_CHANGE));
}


void Transform::SetScale(Vector2& scale)
{
	m_scale = scale;
	m_pGameObject->GetComponentHub()->SendEvent(ComponentHub::Type::ALL, Event(Event::Type::GAMEOBJECT_TRANSFORM_CHANGE));
}


void Transform::SetRotation(float rotation)
{
	m_rotationZ = rotation;
	m_pGameObject->GetComponentHub()->SendEvent(ComponentHub::Type::ALL, Event(Event::Type::GAMEOBJECT_TRANSFORM_CHANGE));
}


void Transform::SetFippping(bool isFlipping)
{
	m_flipping = isFlipping;
	m_pGameObject->GetComponentHub()->SendEvent(ComponentHub::Type::ALL, Event(Event::Type::GAMEOBJECT_TRANSFORM_CHANGE));
}


void Transform::SetParent(Transform* parent)
{
	m_pParent = parent;
	m_position -= m_pParent->GetPosition();
}


GameObject* Transform::GetGameobject() const
{
	return m_pGameObject;
}


Vector2 Transform::GetPosition(float width, float height) const
{
	if (m_pParent)
		return Vector2::GetDesVector(D2D1::Point2F(
			GetMatrix(width, height)._31 + width * 0.5 * m_pParent->GetScale().x,
			GetMatrix(width, height)._32 + height * 0.5 * m_pParent->GetScale().y
			));
	else
		return GetLocalPosition();
}


Vector2 Transform::GetLocalPosition() const
{
	return m_position;
}


D2D1_POINT_2F Transform::GetScreenPosition() const
{
	return GetPosition().GetScreenVector();
}


Vector2 Transform::GetScale() const
{
	return m_scale;
}


float Transform::GetRotation() const
{
		return m_rotationZ;
}


float Transform::GetLocalRotation() const
{
	return m_rotationZ;
}


Transform* Transform::GetParent() const
{
	return m_pParent;
}


D2D1_MATRIX_3X2_F Transform::GetMatrix(float width, float height) const
{
	D2D1_MATRIX_3X2_F resultMatrix;

	D2D1_MATRIX_3X2_F cameraMatrix;
	D2D1_MATRIX_3X2_F posMatrix;
	D2D1_MATRIX_3X2_F rotMatrix;
	D2D1_MATRIX_3X2_F scaleMatrix;
	// 부모 회전 행렬.
	D2D1_MATRIX_3X2_F parentRotMatrix;
	// 부모를 기준으로 돌기 전의 위치.
	Vector2 noRotPosition;
	
	if (m_pParent)
		noRotPosition = GetLocalPosition() + m_pParent->GetPosition();
	else
		noRotPosition = GetLocalPosition();


	if (m_pParent)
		parentRotMatrix = D2D1::Matrix3x2F::Rotation(m_pParent->GetRotation(), m_pParent->GetPosition().GetScreenVector());


		rotMatrix = D2D1::Matrix3x2F::Rotation(
			GetRotation(),
			noRotPosition.GetScreenVector()
			);

		if (m_pParent)
			rotMatrix = rotMatrix * parentRotMatrix;

		if(m_pParent == nullptr)
			posMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(
				noRotPosition.GetScreenVector().x - width * 0.5 * GetScale().x,
				noRotPosition.GetScreenVector().y - height * 0.5* GetScale().y
				));
		else
		{
			posMatrix = D2D1::Matrix3x2F::Translation(D2D1::SizeF(
				Vector2::GetScreenVectorX(
				m_pParent->GetPosition().x + (GetLocalPosition().x - width * 0.5 * GetScale().x) * m_pParent->GetScale().x),
				Vector2::GetScreenVectorY(
				m_pParent->GetPosition().y + (GetLocalPosition().y + height * 0.5 * GetScale().y) * m_pParent->GetScale().y)
				));
			
		}
		if(m_pParent == nullptr)
			scaleMatrix = D2D1::Matrix3x2F::Scale(
				GetScale().x,
				GetScale().y
				);
		else
			scaleMatrix = D2D1::Matrix3x2F::Scale(
				GetScale().x * m_pParent->GetScale().x,
				GetScale().y * m_pParent->GetScale().y
				);

		cameraMatrix = D2D1::Matrix3x2F::Translation( -Camera::GetCameraPos().x, Camera::GetCameraPos().y);
		resultMatrix = scaleMatrix * posMatrix * rotMatrix;

	return resultMatrix;
}


void Transform::Translate(Vector2 dir){
	if (m_pParent)
	{
		if (m_pParent->GetScale().x < 0)
			dir.x *= -1;
		if (m_pParent->GetScale().y < 0)
			dir.y *= -1;
	}
	m_position = m_position + dir;

	m_pGameObject->GetComponentHub()->SendEvent(ComponentHub::Type::ALL, Event(Event::Type::GAMEOBJECT_TRANSFORM_CHANGE));
}


void Transform::Rotate(float z)
{
	SetRotation(m_rotationZ + z);
}