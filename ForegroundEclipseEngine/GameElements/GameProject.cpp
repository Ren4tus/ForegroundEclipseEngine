#include "GameProject.h"
#include "Scene.h"
#include "GameObject.h"
GameProject* GameProject::instance = nullptr;
GameProject::GameProject() {
	
}
void GameProject::CreateObject()
{
	m_scenes.push_back(new Scene());
	for (std::vector<Scene*>::iterator iter = m_scenes.begin();
		iter != m_scenes.end();
		iter++)
	{
		(*iter)->AddGameObejct(new GameObject());
	}
}

GameProject* GameProject::getIncetance()
{
	if (instance == nullptr)
		instance = new GameProject();

	return instance;
}

void GameProject::SaveWorldFile()
{
}

