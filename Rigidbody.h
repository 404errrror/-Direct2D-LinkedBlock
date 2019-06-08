#pragma once
class Rigidbody : public Component
{
public:
	Rigidbody();
	~Rigidbody();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetMass(float mass);
	float GetMass();
	void Collision(BoxCollider* coll);

	static std::list<Rigidbody*> list;
private:
	BoxCollider*	m_pBoxCollider;
	Transform*		m_pTransform;
	float			m_mass;

};

