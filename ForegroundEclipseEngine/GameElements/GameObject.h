#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include "Monobehavior.h"
#include "../Components/glCameraComponent.h"
#include "../Components/glMeshComponent.h"
class Scene;
class Transform;
class IMesh;
class GameObject : Object
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject();

	template<class T>
	T* GetComponent();
	// ��ȯ�� : �߰��� ������Ʈ
	template<class T>
	T* AddComponent(T* component);
	// ��ȯ�� : ���� ����
	template<class T>
	bool RemoveComponent(T* component);

	inline GameObject* GetParent() { return parent; }

	void AddChild(GameObject* childGameobject);
	bool RemoveChild(GameObject* gameobject);
	void MatrixPropagation();
	void SetPosition(glm::vec3 vector);
	void Translate(glm::vec3 vector);
	void Rotate(glm::vec3 vector);
	void SetScale(glm::vec3 vector);
	void Instantiate();
	void SetParent(GameObject* GO);
	Transform* GetTransform();

	// --------------- On, Off, Component, Behaviour, Mono ��� ���� ---------------
	void Awake();
	// --------------- On ������ Mono ���� ���� ---------------
	void Start();
	void FixedUpdate();
	void Update();
	void Render();
	// -----------------------------------------------------------------------------------
	bool IsValid(Component* comp);

	Scene* ownerScene;
	//������İ� �Ϸ�� ������ǥ
	glm::vec3 m_worldPosition;
	glm::vec3 m_worldRotate;
	glm::vec3 m_worldScale;

private:
	IMesh* meshComponent;
	GameObject* parent;
	std::vector<Component*> m_components;
	std::vector<GameObject*> m_childGameobjects;
	std::string m_name;
	unsigned int ID;
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
			return temp;
		}
	}

	return temp;
}
template<class T>
inline T* GameObject::AddComponent(T* component)
{
	bool isThisComponentAlredayExist = false;

	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		if ((dynamic_cast<T*>(*iter)) != NULL) {
			isThisComponentAlredayExist = true;
			return nullptr;
		}
	}

	if (!isThisComponentAlredayExist) {
		m_components.push_back(component);
		component->SetOwner(this);
	}

	return component;
}

template<class T>
inline bool GameObject::RemoveComponent(T* component)
{
	bool isThisComponentExist = false;

	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		if ((dynamic_cast<T*>(*iter)) != NULL) {
			delete (*iter);
			m_components.erase(iter);
			return true;
		}
	}

	return false;
}
