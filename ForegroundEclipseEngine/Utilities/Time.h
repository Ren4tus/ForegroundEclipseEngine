#pragma once
#include <Windows.h>

class Time {
private:
	LARGE_INTEGER timer;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

public:
	static Time& getIncetance();
	Time();
	~Time();
	void StartTimer();
	void EndTimer();
	float m_deltaTime;
	float m_tick;
};
