#include "Scene.h"
#include "GameObject.h"
#include "../Utilities/Time.h"
Scene::Scene() 
	:m_fixedUpdateCounter(0)
{
	m_IsGameEnd = false;
	time = new Time();
}
Scene::Scene(std::string name)
{
	m_name = name;
	time = new Time();
}
Scene::~Scene()
{
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		//TODO: 컴포넌트도 삭제
		delete (*iter);
	}
}
void Scene::Loop()
{
	//awake

	//start
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		(*iter)->Start();
	}

	while (!m_IsGameEnd) {
		time->StartTimer();

		//Update
		if (time->m_tick > UPDATE_EXECUTE_TIME) {
			for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
				iter != m_ManagedGameObjects.end();
				iter++)
			{
				(*iter)->Update();

			}
			time->m_tick = 0.0f;
			m_fixedUpdateCounter++;
		}

		//FixedUpdtae 함수 호출
		if (m_fixedUpdateCounter > FIXED_EXECUTE_TIME) {
			for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
				iter != m_ManagedGameObjects.end();
				iter++)
			{
				(*iter)->FixedUpdate();
			}
			m_fixedUpdateCounter = 0;
		}

		time->EndTimer();
	}


}

void Scene::AddGameObejct(GameObject* GO)
{
	m_ManagedGameObjects.push_back(GO);
}

Time* Scene::GetTime()
{
	return time;
}
