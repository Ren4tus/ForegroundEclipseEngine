#pragma once
#include "EngineSystem.h"
#include "../../pch.h"
#include "../../GameElements/Scene.h"

class glEvents;
class glCameraComponent;

class glSystem : public EngineSystem{
public:
	glSystem();
	glSystem(std::string GameName);
	~glSystem();

	inline const bool IsRunning() const { return run; }
	inline GLFWwindow& Window() { return *window; }

	virtual bool BuildSystem() override;
	virtual bool SystemInit() override;
	virtual bool Run() override; 
	virtual Scene* GetSceneRoot() override;
	virtual void SetRootScene(Scene* scene) override;
	GLFWwindow* GetWindow() {return window;}
private:
	bool run;
	GLFWwindow* window;
	glCameraComponent* camera = nullptr;
};
