#pragma once
class EnemyInterface
{
public:
	virtual void Attack() = 0;
	virtual void Die() = 0;
	virtual void Hitted(int attack) = 0;
	virtual void Respawn(Vector2) = 0;
protected:
	unsigned int m_hp;
	unsigned int m_attack;
	float m_speed;
};

