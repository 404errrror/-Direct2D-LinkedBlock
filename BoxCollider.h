#pragma once


class BoxCollider : public Component
{
public:
	BoxCollider();
	~BoxCollider();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int		Start		();
	virtual int		Update		();
			void	Debug		();
	virtual int		OnEvent		(Event&);

	void			SetRange	(D2D1_RECT_F detectRect);
	void			SetRange	(float width, float height);
	void			SetTrigger	(bool isTrigger);

	D2D1_RECT_F		GetRange	() const;
	// mass�� Rigidbody�κ��� �޾ƿɴϴ�. 
	//���� Rigidbody�� ���ٸ� -1�� ��ȯ�մϴ�.
	float			GetMass		() const;
	bool			IsTrigger() const;
	bool			DetectCollision(BoxCollider*& targetRect) const;
	bool			DetectCollision(Vector2& vector) const;

	static std::list<BoxCollider*> list;
	Transform* m_pTransfrom;
private:
	ID2D1BitmapBrush* m_pGreenBrush;

	float left, top, right, bottom;
	Vector2 center;
	bool isTrigger;
};

class BoxColliderSort
{
public:
	// ���� ����.
	bool operator()(const BoxCollider* a, const BoxCollider* b)const
	{

		return a->m_pTransfrom->GetScreenPosition().y + a->GetRange().bottom <
			b->m_pTransfrom->GetScreenPosition().y + b->GetRange().bottom;
	}
};