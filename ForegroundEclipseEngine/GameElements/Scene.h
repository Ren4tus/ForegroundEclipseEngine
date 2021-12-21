#pragma once
#include <vector>
#include <string>
#include "../pch.h"
#include "../EngineSystem/glSystem/Shaders/shaderClass.h"
#include "GameObject.h"
class Component;

class Scene
{
public:
	Scene();
	Scene(std::string);
	~Scene();

	void Awake();
	void Start();
	void Run();
	void Render();
	void AddGameObject(GameObject* GO);
	void ResetGameObjectWorldPosition();
	void SetThisComponentToSceneCamera(Component* cameraComp);
	glCameraComponent* GetGLSceneCamera();

	//OpenGL 전용 함수
	bool SetSkyBox(Shader& shader, std::string FolderPath);
	//SkyBox는 렌더링의 마지막에 수행되어야 함.
	bool DrawSkyBox();
	bool SetDirectionalLight(Shader& shader);

private:
	Component* cameraComponent;
	std::vector<GameObject*> m_ManagedGameObjects;
	bool m_IsGameEnd;
	std::string m_name;

	//skybox
	Shader* skyboxShader;
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	unsigned int cubemapTexture;

	//direct light
	Shader* directLightShader;

};