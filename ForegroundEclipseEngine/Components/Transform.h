#pragma once
#include <string>
#include "../pch.h"
#include "../GameElements/Monobehavior.h"
#include "../GameElements/Component.h"
class Transform : public Component
{
public:
	Transform();
	~Transform();
public:
	void Translate(glm::vec3 translateVector);
	void Rotate(glm::vec3 rotateVector);
	void Scale(glm::vec3 scaleVector);
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
private:
	std::string m_name;

};
