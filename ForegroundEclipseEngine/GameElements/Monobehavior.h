#pragma once

#include "Behaviour.h"

// �ڷ�ƾ, ȣ�� �Ǵ� ���� OnCollisionEnter�Լ�, Start, OnEnable, ��� ���� Unity �ݹ� �Լ��� ���.
// ���� Update���� Mono���� ����

class Monobehavior : public Behaviour{
public:
	virtual ~Monobehavior(){}
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
};