#pragma once
class CRandom
{
public:
	CRandom();
	~CRandom();

	// min���� max���� �������� ��ȯ�մϴ�. (min�� max�� �����մϴ�.)
	static int		Range(int min, int max);
	static float	Range(double min, double max);
};

