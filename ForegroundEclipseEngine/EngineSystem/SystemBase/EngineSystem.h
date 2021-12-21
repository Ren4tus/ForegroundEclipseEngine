#pragma once
#include <string>
#include <memory>
class Scene;
class EngineSystem
{
public:
	EngineSystem(){}
	

	~EngineSystem(){}

public:
	virtual bool BuildSystem() = 0;
	virtual bool SystemInit() = 0;
	virtual bool Run() = 0;
	virtual Scene* GetSceneRoot() = 0;
	virtual void SetRootScene(Scene* scene) = 0;
	void SetDisplayFPS(bool option) { bDisplayFPS = option; }

	std::string EngineType;

protected:
	Scene* gameScene;
	bool bDisplayFPS = true;

};
