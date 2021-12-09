#pragma once
#include "Component.h"
/// <summary>
/// ON-OFF 가능한 컴포넌트 (내장 스크립트 전용. 커스텀 클래스는 직접 상속하면 안됨)
/// </summary>
class Behaviour : public Component
{
public:
	Behaviour()
	{
	}
	virtual ~Behaviour() = 0;
private:
	//이 기능이 활성화 되는 경우 behavior가 업데이트되고, 비활성화 되는 경우 behavior는 업데이트 되지 않음.
	bool enabled;
};
