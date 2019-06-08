#pragma once
#include <time.h>

// ����Ŭ���� �Դϴ�. ��ü�� ������ �ʿ�����ϴ�.
class Time
{
public:
	Time();
	~Time();

	static void Initialize();
	static void Refresh();
	static float GetDeltaTime();

private:
	static INT64 startTime;
	static INT64 beforeTime;
	static INT64 nowTime;
	static float deltaTime;
};

