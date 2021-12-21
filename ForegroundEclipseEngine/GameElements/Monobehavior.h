#pragma once

#include "Behaviour.h"

// 코루틴, 호출 또는 물리 OnCollisionEnter함수, Start, OnEnable, 등과 같은 Unity 콜백 함수를 사용.
// 따라서 Update류는 Mono에만 존재

class Monobehavior : public Behaviour{
public:
	virtual ~Monobehavior(){}
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
};