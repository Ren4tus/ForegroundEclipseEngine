#pragma once
#include <Windows.h>

class Time {
public:
	~Time();
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	static Time& Ref() {
		static Time reference;
		return reference;
	}
	double prevTime = 0.0;
	double crntTime = 0.0;
	double DeltaTime;
	unsigned int counter = 0;
	const float frame = 1.0f / 30.0f;
private:
	Time();

};
static Time& SDLTimer = Time::Ref();