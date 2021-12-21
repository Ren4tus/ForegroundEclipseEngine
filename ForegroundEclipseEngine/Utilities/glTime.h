#pragma once
class glTime {
public:
	~glTime();
	glTime(const glTime&) = delete;
	glTime& operator=(const glTime&) = delete;

	static glTime& Ref() {
		static glTime reference;
		return reference;
	}
	double prevTime = 0.0;
	double crntTime = 0.0;
	double DeltaTime;
	unsigned int counter = 0;
	const float frame = 1.0f / 30.0f;
private:
	glTime();
};

static glTime& glTimer = glTime::Ref();
