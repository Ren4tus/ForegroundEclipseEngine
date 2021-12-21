#pragma once
#include "Component.h"
// ON-OFF ������ ������Ʈ (���� ��ũ��Ʈ ����. Ŀ���� Ŭ������ ���� ����ϸ� �ȵ�)
class Behaviour : public Component
{
public:
	Behaviour()
	{
	}
	virtual ~Behaviour() {}

	virtual void SetActive(bool isActive) { enabled = isActive; }
	bool IsActive() { return enabled; }

protected:
	//�� ����� Ȱ��ȭ �Ǵ� ��� behavior�� ������Ʈ�ǰ�, ��Ȱ��ȭ �Ǵ� ��� behavior�� ������Ʈ ���� ����.
	//�⺻���� true
	bool enabled = true;
};
