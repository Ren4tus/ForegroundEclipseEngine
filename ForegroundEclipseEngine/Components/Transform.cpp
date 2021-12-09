#include "Transform.h"
Transform::Transform()
{
	m_name = "Transform";
	m_position.x = 0.0;
	m_position.y = 0.0;
	m_position.z = 0.0;
	m_scale.x = 1.0;
	m_scale.y = 1.0;
	m_scale.z = 1.0;
}

Transform::~Transform()
{
}


void Transform::Translate(Vector3D translateVector)
{
	m_position.x += translateVector.x;
	m_position.y += translateVector.y;
	m_position.z += translateVector.z;
}
