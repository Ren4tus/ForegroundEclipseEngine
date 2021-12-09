#pragma once
#include "Object.h"
/// <summary>
/// on-off 불가능한 컴포넌트 & 내장 스크립트 -> 리지드바디 등. 커스텀 컴포넌트가 직접 상속하면 안됨
/// </summary>
class Component : public Object
{
public:
	Component()
	{
	}
	virtual ~Component() = 0;
public:
	//현재 컴포넌트가 첨부된 게임 오브젝트
	//GameObject gameObject;
};
