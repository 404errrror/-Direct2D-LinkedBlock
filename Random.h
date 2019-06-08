#pragma once
class CRandom
{
public:
	CRandom();
	~CRandom();

	// min부터 max까지 랜덤값을 반환합니다. (min과 max를 포함합니다.)
	static int		Range(int min, int max);
	static float	Range(double min, double max);
};

