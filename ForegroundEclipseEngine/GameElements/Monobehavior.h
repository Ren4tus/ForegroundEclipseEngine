#pragma once
//#include <vector>
#include "Behaviour.h"
/// <summary>
/// �ڷ�ƾ, ȣ�� �Ǵ� ���� OnCollisionEnter�Լ�, Start, OnEnable, ��� ���� Unity �ݹ� �Լ��� ���.
/// ���� Update���� Mono���� ����
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