#pragma once
#include <time.h>

// 전역클래스 입니다. 객체를 생성할 필요없습니다.
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

