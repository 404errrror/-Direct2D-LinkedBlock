#include "stdafx.h"
#include "Time.h"

// 정적변수 초기화
INT64 Time::startTime;
INT64 Time::beforeTime;
INT64 Time::nowTime;
float Time::deltaTime;
Time::Time()
{
}


Time::~Time()
{
}

void Time::Initialize()
{
	nowTime = startTime = clock();
}


void Time::Refresh()
{
	beforeTime = nowTime;
	nowTime = clock();
	deltaTime = (nowTime - beforeTime) * 0.001;
}


float Time::GetDeltaTime()
{
	return deltaTime;
}