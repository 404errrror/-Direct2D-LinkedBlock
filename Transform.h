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
	// true : 카메라 효과를 받지 않습니다. false : Default

	// GameObject는 안넣을려했는데 Event때문에 어쩔수 없이.
	GameObject*			GetGameobject		() const;
	Vector2				GetPosition			(float width = 0, float height = 0) const;
	Vector2				GetLocalPosition	() const;
	D2D1_POINT_2F		GetScreenPosition	() const;
	Vector2				GetScale			() const;
	float				GetRotation			() const;
	float				GetLocalRotation	() const;
	Transform*			GetParent			() const;
	// 이미지크기말고 다른 크기도 있기 때문에 받아와야한다.
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

