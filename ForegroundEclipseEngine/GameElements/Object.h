#pragma once
#include <string>
class Object
{
public:
	Object() {}
	virtual ~Object() = 0;

protected:
	std::string name;
	std::string ID;
public:
	std::string GetInstanceID() { return ID; }
	std::string GetName() { return name; }
	//오브젝트가 숨겨져있는 상태인지, 씬에 저장된 상태인지, 또는 사용자에 의해서 수정가능한 상태인지
	bool hideFlags;
};
