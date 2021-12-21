#pragma once
#include <string>
#include <fstream>
class EngineSystem;
class Component;
class GameObject;
class GameManager {
public:
	~GameManager();
	static GameManager* Instance();

	void SetCurrentEngine(EngineSystem* engine) { currentEngine = engine; }
	void SetGameName(std::string name) { gameName = name; }
	std::string GetEngineType() { return engineType; }
	void SetEngineType(std::string type) { engineType = type; }
	void setWindowScreen(unsigned int width, unsigned int height) { windowWidth = width; windowHeight = height; }
	unsigned int getWindowWidth() { return windowWidth; }
	unsigned int getWindowHeight() { return windowHeight; }

	EngineSystem* LoadEngineSystemByConfig();
	void ApplySettingsInConfig();
	void QueryComponentType(std::string name, GameObject* target);
	EngineSystem* GetCurrentEngine();
	std::string GetGameName();
	unsigned int IssuingNewID();


private:
	GameManager();

	EngineSystem* QueryEngineType(std::string EngineType);

	static GameManager* s_pInstance;
	std::string ProjectFolderPath;
	std::string ProjectPrimalFilePath;
	EngineSystem* currentEngine;
	std::string gameName;
	std::string engineType;
	unsigned int windowWidth;
	unsigned int windowHeight;
	unsigned int IDCount = 0;
};
typedef GameManager GM;