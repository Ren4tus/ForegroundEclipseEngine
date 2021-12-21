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
	//������Ʈ�� �������ִ� ��������, ���� ����� ��������, �Ǵ� ����ڿ� ���ؼ� ���������� ��������
	bool hideFlags;
};