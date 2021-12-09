#pragma once
#include "Component.h"
/// <summary>
/// ON-OFF ������ ������Ʈ (���� ��ũ��Ʈ ����. Ŀ���� Ŭ������ ���� ����ϸ� �ȵ�)
/// </summary>
class Behaviour : public Component
{
public:
	Behaviour()
	{
	}
	virtual ~Behaviour() = 0;
private:
	//�� ����� Ȱ��ȭ �Ǵ� ��� behavior�� ������Ʈ�ǰ�, ��Ȱ��ȭ �Ǵ� ��� behavior�� ������Ʈ ���� ����.
	bool enabled;
};
