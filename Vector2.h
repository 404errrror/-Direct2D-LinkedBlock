#pragma once

class Vector2
{
public:
	Vector2	();
	Vector2	(float x, float y) : x(x), y(y){}
	~Vector2();


	Vector2 operator + (Vector2);
	Vector2 operator - (Vector2);
	Vector2 operator * (float);
	Vector2 operator -= (Vector2);
	Vector2 operator / (float);

	//��ũ�����ͷ� ��ȯ��Ų ���� �����մϴ�.
	D2D1_POINT_2F			GetScreenVector() const;
	static D2D1_POINT_2F	GetScreenVector(const Vector2& vector);
	static float	GetScreenVectorX(const float& x);
	static float	GetScreenVectorY(const float& y);
	
	// ��ī��Ʈ ���ͷ� ��ȯ��Ų ���� �����մϴ�.
	static Vector2	GetDesVector	(const D2D1_POINT_2F& point);
	static float	GetDesVectorX	(const float& x);
	static float	GetDesVectorY	(const float& y);

	static float	GetDistance		(Vector2 a, Vector2 b);
	static Vector2	Normalize(Vector2);


	float x, y;
};

