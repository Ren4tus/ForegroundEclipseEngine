#pragma once
//#include <vector>
#include "Behaviour.h"
/// <summary>
/// 코루틴, 호출 또는 물리 OnCollisionEnter함수, Start, OnEnable, 등과 같은 Unity 콜백 함수를 사용.
/// 따라서 Update류는 Mono에만 존재
/// </summary>
//class Time;
class Monobehavior : public Behaviour{
private:

public:
	Monobehavior();
	virtual ~Monobehavior() = 0;
	void Start();
	void Update();
	void FixedUpdate();
	void Init();

};