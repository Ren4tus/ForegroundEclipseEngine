#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include "../Utilities/Vector3.h"
#include "Monobehavior.h"
class Transform;
class GameObject : Object
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject();
	template<class T>
	T* GetComponent();

	void AddComponent(Component* newComponent);
	void AddChild(GameObject* childGameobject);
	void SetPosition(double x, double y, double z);
	void AddPosition(Vector3D vec3);
	void SetScale(double x, double y, double z);
	void Instantiate();
	Transform* GetTransform();

	void FixedUpdate();
	void Update();
	void Start();

	//debug
	void DebugNowPosition();
private:
	std::vector<Component*> m_components;
	std::vector<GameObject*> m_childGameobjects;
	Vector3D m_reservationPosition;
	std::stack<Vector3D*> m_reservationScale;
	std::string m_name;
};
template<class T>
inline T* GameObject::GetComponent()
{
	T* temp = nullptr;
	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		if ((dynamic_cast<T*>(*iter)) != NULL) {
			temp = (dynamic_cast<T*>(*iter));
		}

	}

	return temp;
}