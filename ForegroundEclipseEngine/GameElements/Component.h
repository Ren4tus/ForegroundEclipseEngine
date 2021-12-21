#pragma once
#include "Object.h"

// on-off 불가능한 컴포넌트 & 내장 스크립트 -> 리지드바디 등. 커스텀 컴포넌트가 직접 상속하면 안됨
class GameObject;
class Component : public Object
{
public:
	Component(){}
	virtual ~Component() {}
	virtual void testfunc(){}
	void SetOwner(GameObject* GO) { owner = GO; }
protected:
	//이 컴포넌트를 장착한 게임오브젝트
	GameObject* owner;
};
