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
	//������Ʈ�� �������ִ� ��������, ���� ����� ��������, �Ǵ� ����ڿ� ���ؼ� ���������� ��������
	bool hideFlags;
};
