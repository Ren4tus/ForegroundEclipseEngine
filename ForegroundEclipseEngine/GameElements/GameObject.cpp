#include <iostream>
#include "GameObject.h"
#include "../Components/Transform.h"
GameObject::GameObject()
{
	m_name = "GameObject";
	AddComponent(new Transform());
	m_reservationPosition = Vector3D(0.0, 0.0, 0.0);
}
GameObject::GameObject(std::string name)
{
	m_name = name;
	AddComponent(new Transform());
	m_reservationPosition = Vector3D(0.0, 0.0, 0.0);
}
GameObject::~GameObject()
{
	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		delete (*iter);
	}
}
void GameObject::AddComponent(Component* newComponent)
{
	m_components.push_back(newComponent);
}

void GameObject::AddChild(GameObject* childGameobject)
{
	m_childGameobjects.push_back(childGameobject);
}

void GameObject::SetPosition(double x, double y, double z)
{
	m_reservationPosition = Vector3D(x, y, z);
}

void GameObject::AddPosition(Vector3D vec3)
{
	m_reservationPosition.x += vec3.x;
	m_reservationPosition.y += vec3.y;
	m_reservationPosition.z += vec3.z;
}

void GameObject::SetScale(double x, double y, double z)
{
	m_reservationScale.push(new Vector3D(x, y, z));
}

void GameObject::Instantiate()
{

}

Transform* GameObject::GetTransform()
{
	return static_cast<Transform*>(m_components[0]);
}

void GameObject::FixedUpdate()
{
	//DebugNowPosition();
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			if ((dynamic_cast<Monobehavior*>(*compIter)) != NULL) {
				(dynamic_cast<Monobehavior*>(*compIter))->FixedUpdate();
			}
			
		}
	}
	for (std::vector<Component*>::iterator mCompiter = m_components.begin();
		mCompiter != m_components.end();
		mCompiter++)
	{
		if ((dynamic_cast<Monobehavior*>(*mCompiter)) != NULL) {
			(dynamic_cast<Monobehavior*>(*mCompiter))->FixedUpdate();
		}
	}
}

void GameObject::Update()
{
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			if ((dynamic_cast<Monobehavior*>(*compIter)) != NULL) {
				(dynamic_cast<Monobehavior*>(*compIter))->Update();
			}
		}
	}
	for (std::vector<Component*>::iterator mCompiter = m_components.begin();
		mCompiter != m_components.end();
		mCompiter++)
	{
		if ((dynamic_cast<Monobehavior*>(*mCompiter)) != NULL) {
			(dynamic_cast<Monobehavior*>(*mCompiter))->Update();
		}
	}
}

void GameObject::Start()
{
	//matrix propagation
	this->GetTransform()->Translate(m_reservationPosition);
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		(*iter)->AddPosition(this->GetTransform()->m_position);
	}

	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			if ((dynamic_cast<Monobehavior*>(*compIter)) != NULL) {
				(dynamic_cast<Monobehavior*>(*compIter))->Start();
			}
		}
	}
	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		if ((dynamic_cast<Monobehavior*>(*iter)) != NULL) {
			(dynamic_cast<Monobehavior*>(*iter))->Start();
		}
	}

}

void GameObject::DebugNowPosition()
{
	Vector3D tempPosition = this->GetTransform()->m_position;
	std::cout << m_name + ": (" << tempPosition.x << "," << tempPosition.y << "," << tempPosition.z << ")" << std::endl;
}

