#include "Transform.h"
Transform::Transform()
{
	m_name = "Transform";
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}


void Transform::Translate(glm::vec3 vector)
{
	m_position += vector;
}
void Transform::Rotate(glm::vec3 rotateVector)
{
	m_rotation += rotateVector;
}
void Transform::Scale(glm::vec3 scaleVector)
{
	m_scale += scaleVector;
}