#pragma once
#include "Object.h"
/// <summary>
/// on-off �Ұ����� ������Ʈ & ���� ��ũ��Ʈ -> ������ٵ� ��. Ŀ���� ������Ʈ�� ���� ����ϸ� �ȵ�
/// </summary>
class Component : public Object
{
public:
	Component()
	{
	}
	virtual ~Component() = 0;
public:
	//���� ������Ʈ�� ÷�ε� ���� ������Ʈ
	//GameObject gameObject;
};
