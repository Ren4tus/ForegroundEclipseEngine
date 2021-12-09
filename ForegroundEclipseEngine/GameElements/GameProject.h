#pragma once
#include <vector>
//#include "Scene.h"
class Scene;
class GameProject {
private:
	GameProject();
	GameProject(const GameProject& ref);
	GameProject& operator=(const GameProject& ref) {}
	~GameProject() {}
	static GameProject* instance;
	std::vector<Scene*> m_scenes;
public:
	static GameProject* getIncetance();
	static void SaveWorldFile();
	void CreateObject();
};