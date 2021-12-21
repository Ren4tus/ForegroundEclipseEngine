#include <iostream>
#include "GameObject.h"
#include "../Components/Transform.h"
#include "Scene.h"
#include "../EngineSystem/GameManager.h"
GameObject::GameObject()
{
	//�θ�� ���� ���� ������ ��Ʈ = null
	parent = nullptr;

	m_name = "GameObject";
	AddComponent(new Transform());
}
GameObject::GameObject(std::string name)
{
	//�θ�� ���� ���� ������ ��Ʈ = null
	parent = nullptr;

	m_name = name;
	AddComponent(new Transform());
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

void GameObject::AddChild(GameObject* childGameobject)
{
	m_childGameobjects.push_back(childGameobject);
	// �ڽİ�ü�� �θ�� �� ������Ʈ
	childGameobject->SetParent(this);
	// �ڽİ�ü�� ���� ��Ͻ����ش�
	ownerScene->AddGameObject(childGameobject);
}

bool GameObject::RemoveChild(GameObject* gameobject)
{
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		if ((*iter)->GetInstanceID() == gameobject->GetInstanceID()) {
			m_childGameobjects.erase(iter);
			(*iter)->SetParent(nullptr);
			// �θ𿡼� �������� ���� ��ǥ�� �����ǥ�� ���������� ��
			(*iter)->GetTransform()->m_position = (*iter)->m_worldPosition;
			(*iter)->GetTransform()->m_rotation = (*iter)->m_worldRotate;
			(*iter)->GetTransform()->m_scale = (*iter)->m_worldScale;
			return true;
		}
	}
	return false;
}

void GameObject::MatrixPropagation()
{
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		(*iter)->m_worldPosition += this->GetTransform()->m_position;
	}
}

void GameObject::SetPosition(glm::vec3 vector)
{
	GetTransform()->m_position = vector;
}

void GameObject::Translate(glm::vec3 vector)
{
	GetTransform()->m_position += vector;
}

void GameObject::Rotate(glm::vec3 vector)
{
	GetTransform()->m_rotation = vector;
}

void GameObject::SetScale(glm::vec3 vector)
{
	GetTransform()->m_scale = vector;
}

void GameObject::Instantiate()
{
}

void GameObject::SetParent(GameObject* GO)
{
	parent = GO;
}

Transform* GameObject::GetTransform()
{
	return static_cast<Transform*>(m_components[0]);
}

void GameObject::Awake()
{
	ID = GM::Instance()->IssuingNewID();
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			(*compIter)->SetInstanceID(GM::Instance()->IssuingNewID());
		}
	}
	for (std::vector<Component*>::iterator mCompiter = m_components.begin();
		mCompiter != m_components.end();
		mCompiter++)
	{
		(*mCompiter)->SetInstanceID(GM::Instance()->IssuingNewID());
	}
}

void GameObject::FixedUpdate()
{
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			if (IsValid(*compIter))
			{
				(dynamic_cast<Monobehavior*>(*compIter))->FixedUpdate();
			}
		}
	}
	for (std::vector<Component*>::iterator mCompiter = m_components.begin();
		mCompiter != m_components.end();
		mCompiter++)
	{
		if (IsValid(*mCompiter)) {
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
			if (IsValid(*compIter))
			{
				(dynamic_cast<Monobehavior*>(*compIter))->Update();
			}
		}
	}
	for (std::vector<Component*>::iterator mCompiter = m_components.begin();
		mCompiter != m_components.end();
		mCompiter++)
	{
		if (IsValid(*mCompiter))
		{
			(dynamic_cast<Monobehavior*>(*mCompiter))->Update();
		}
	}
}

void GameObject::Start()
{
	for (std::vector<GameObject*>::iterator iter = m_childGameobjects.begin();
		iter != m_childGameobjects.end();
		iter++)
	{
		for (std::vector<Component*>::iterator compIter = (*iter)->m_components.begin();
			compIter != (*iter)->m_components.end();
			compIter++)
		{
			if (IsValid(*compIter))
			{
				(dynamic_cast<Monobehavior*>(*compIter))->Start();
			}
		}
	}
	for (std::vector<Component*>::iterator iter = m_components.begin();
		iter != m_components.end();
		iter++)
	{
		if (IsValid(*iter)) {
			(dynamic_cast<Monobehavior*>(*iter))->Start();
		}
	}
}

void GameObject::Render()
{
	meshComponent = GetComponent<IMesh>();
	if (meshComponent != nullptr) {
		if ((dynamic_cast<Behaviour*>(meshComponent))->IsActive() == true) {
			(dynamic_cast<IMesh*>(meshComponent))->DrawMesh();
		}
	}
}

bool GameObject::IsValid(Component* comp)
{
	Monobehavior* tempCastedComp = dynamic_cast<Monobehavior*>(comp);

	if (
		tempCastedComp != NULL &&
		tempCastedComp->IsActive() == true
		)
	{
		return true;
	}
	return false;
}