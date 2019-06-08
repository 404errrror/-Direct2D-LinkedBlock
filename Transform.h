#pragma once
#include "Component.h"
class Transform : public Component
{
public:
	Transform();
	~Transform();
	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start	();
	virtual int Update	();
	virtual int OnEvent	(Event&);

	void SetPosition	(Vector2& postion);
	void SetScale		(Vector2& scale);
	void SetRotation	(float rotation);
	void SetFippping	(bool isFlipping);
	void SetParent		(Transform* parent);
	// true : ī�޶� ȿ���� ���� �ʽ��ϴ�. false : Default

	// GameObject�� �ȳ������ߴµ� Event������ ��¿�� ����.
	GameObject*			GetGameobject		() const;
	Vector2				GetPosition			(float width = 0, float height = 0) const;
	Vector2				GetLocalPosition	() const;
	D2D1_POINT_2F		GetScreenPosition	() const;
	Vector2				GetScale			() const;
	float				GetRotation			() const;
	float				GetLocalRotation	() const;
	Transform*			GetParent			() const;
	// �̹���ũ�⸻�� �ٸ� ũ�⵵ �ֱ� ������ �޾ƿ;��Ѵ�.
	D2D1_MATRIX_3X2_F	GetMatrix			(float width, float height) const;

	void				Translate(Vector2 dir);
	void				Rotate(float z);

private:
	Vector2			m_position;
	Vector2			m_scale;
	float			m_rotationZ;
	bool			m_flipping;
	Transform*		m_pParent;
};

