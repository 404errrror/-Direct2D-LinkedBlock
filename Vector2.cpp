#include "stdafx.h"
#include "Vector2.h"


Vector2::Vector2()
{
	x = y = 0;
}


Vector2::~Vector2()
{
}


Vector2 Vector2::operator+(Vector2 a)
{
	return Vector2(x + a.x, y + a.y);
}


Vector2 Vector2::operator-(Vector2 a)
{
	return Vector2(x - a.x, y - a.y);
}


Vector2 Vector2::operator * (float a)
{
	return Vector2(x * a, y * a);
}


Vector2 Vector2::operator -= (Vector2 a)
{
	return Vector2(x - a.x, y - a.y);
}


Vector2 Vector2::operator / (float a)
{
	return Vector2(x / a, y / a);
}


D2D1_POINT_2F Vector2::GetScreenVector() const
{
	return GetScreenVector(Vector2(x,y));
}

D2D1_POINT_2F Vector2::GetScreenVector(const Vector2& vector2)
{

	D2D1_POINT_2F result;

	result.x = GetScreenVectorX(vector2.x);
	result.y = GetScreenVectorY(vector2.y);

	return result;
}


float Vector2::GetScreenVectorX(const float& x)
{
	float result;
	result = x + (MAX_SCREEN_WIDTH - g_windowRight) * 0.5;
	return result;
}


float Vector2::GetScreenVectorY(const float& y)
{
	float result = y;
	result -= (MAX_SCREEN_HEIGHT - g_windowTop) * 0.5;
	result *= -1;
	return result;
}



Vector2 Vector2::GetDesVector(const D2D1_POINT_2F& point)
{
	Vector2 result;
	result.x = GetDesVectorX(point.x);
	result.y = GetDesVectorY(point.y);
	
	return result;
}


float Vector2::GetDesVectorX(const float& x)
{
	float result = x;
	result -= (MAX_SCREEN_WIDTH - g_windowRight) * 0.5;

	return result;
}



float Vector2::GetDesVectorY(const float& y)
{
	float result = y;
	result *= -1;
	result += (MAX_SCREEN_HEIGHT - g_windowTop) * 0.5;

	return result;
}


float Vector2::GetDistance(Vector2 a, Vector2 b)
{
	Vector2 sub = a - b;
	return sqrt(sub.x * sub.x + sub.y * sub.y);
}


Vector2 Vector2::Normalize(Vector2 vector)
{
	if (vector.x == 0 && vector.y == 0)
		return Vector2(0,0);
	else
		return  vector / sqrt(vector.x * vector.x + vector.y * vector.y);
}