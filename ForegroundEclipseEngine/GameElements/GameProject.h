#pragma once
#include <vector>
#include "../Common/Singleton.h"
class Scene;
class GameProject : public Singleton<GameProject> {
private:
	GameProject();
	GameProject(const GameProject& ref);
	GameProject& operator=(const GameProject& ref) {}
	~GameProject() {}
	std::vector<Scene*> m_scenes;
public:
	static void SaveWorldFile();
	void CreateObject();
};