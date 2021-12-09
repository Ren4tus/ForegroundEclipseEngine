#pragma once
#include <string>
#include "../Utilities/Vector3.h"
#include "../GameElements/Monobehavior.h"
#include "../GameElements/Component.h"
class Transform : public Component
{
public:
	Transform();
	~Transform();
	void Translate(Vector3D translateVector);

	Vector3D m_position;
	Vector3D m_scale;
private:
	std::string m_name;

};
