#pragma once
#include "Object.h"

// on-off �Ұ����� ������Ʈ & ���� ��ũ��Ʈ -> ������ٵ� ��. Ŀ���� ������Ʈ�� ���� ����ϸ� �ȵ�
class GameObject;
class Component : public Object
{
public:
	Component(){}
	virtual ~Component() {}
	virtual void testfunc(){}
	void SetOwner(GameObject* GO) { owner = GO; }
protected:
	//�� ������Ʈ�� ������ ���ӿ�����Ʈ
	GameObject* owner;
};
