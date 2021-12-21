#pragma once
#include <string>
class Object
{
public:
	Object() {}
	virtual ~Object() = 0;

	inline unsigned int GetInstanceID() { return ID; }
	inline void SetInstanceID(unsigned int _ID) { this->ID = _ID; }
	inline std::string GetName() { return name; }
protected:
	std::string name;
	unsigned int ID;
public:
	//오브젝트가 숨겨져있는 상태인지, 씬에 저장된 상태인지, 또는 사용자에 의해서 수정가능한 상태인지
	bool hideFlags;
};