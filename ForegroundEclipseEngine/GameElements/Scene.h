#pragma once
#include <vector>
#include <string>
class Time;
class GameObject;
class Scene
{
public:
	Scene();
	Scene(std::string);
	~Scene();

	void Loop();
	void AddGameObejct(GameObject* GO);
	Time* GetTime();
private:
	std::vector<GameObject*> m_ManagedGameObjects;
	bool m_IsGameEnd;
	std::string m_name;

	Time* time;
	const unsigned short FIXED_EXECUTE_TIME = 2;
	const float UPDATE_EXECUTE_TIME = 3.0f;
	unsigned short m_fixedUpdateCounter;
};