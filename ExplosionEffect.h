#pragma once
class ExplosionEffect
	: GameObject
{
public:
	ExplosionEffect();
	~ExplosionEffect();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();

	void SetParent(Transform* parent);
	void SetAmount(int amount);
	void SetSpeed(float speed);
	void SetColor(D2D1_COLOR_F& color);

	void Play();
	void Stop();

private:
	void SetParticleActive();

	std::list<GameObject*> particleList;
	Vector2* directArr;
	int m_amount;
	float m_speed;
};

