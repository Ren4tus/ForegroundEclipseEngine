#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/glSystem.h"
#include "../ForegroundEclipseEngine/EngineSystem/GameManager.h"
#include "../ForegroundEclipseEngine/GameElements/Scene.h"
#include "../ForegroundEclipseEngine/GameElements/GameObject.h"
#include "../ForegroundEclipseEngine/pch.h"
#include "OrphanMaker.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

// 01. GL ������ �ε� & ť�� ���

int main(int argv, char** args){

	// --------------- ���� ���� ----------------
	
	// GL �ý��� �ε�
	EngineSystem* engineSystem = new glSystem();
	engineSystem->BuildSystem();

	// --------------- ���� ��� ���� ----------------

	// �� ����
	Scene* scene = new Scene();
	// ��Ʈ ������ ����
	engineSystem->SetRootScene(scene);

	// ���� ������Ʈ ����
	GameObject* test = new GameObject("parent");
	GameObject* cube = new GameObject("cube");
	GameObject* camera = new GameObject("camera");
	glCameraComponent* newCamera = new glCameraComponent(800, 600, glm::vec3(0.0f, 0.0f, 0.0f));
	scene->SetThisComponentToSceneCamera(newCamera);
	scene->AddGameObject(test);
	scene->AddGameObject(camera);

	// ��� ���� �׽�Ʈ
	// �̵� �� �ڽ��� ���̰ų� �ڽ��� ���̰� �̵��ϰų� ��� ó���ǵ��� ����
	test->Translate(glm::vec3(0.0f, 5.0f, 0.0f));
	test->AddChild(cube);

	// �θ� ���ִ� �׽�Ʈ�� ������Ʈ - R �� ������ �θ� / �ڽ� ���� ����
	// �θ𿡼� ������ ���͵� �ڽ��� ���� ��ġ�� �����Ǵ��� �׽�Ʈ
	test->AddComponent<OrphanMaker>(new OrphanMaker(test, cube));

	// directLight�� skybox�� Shader ����
	Shader directLight("default.vert", "default.frag");
	scene->SetDirectionalLight(directLight);

	// �Ž� ����
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/models/cube/BoxTextured.gltf";
	glMeshComponent* newmesh = new glMeshComponent((parentDir + modelPath).c_str());
	cube->AddComponent<glMeshComponent>(newmesh);

	// --------------- ���� ���� ----------------
	engineSystem->Run();

	// --------------- ���� ----------------

	// ������ ���̴� �Ҵ� ����
	directLight.Delete();

	// ���� �ý��� �Ҵ� ����
	delete engineSystem;

	return 0;
}
