#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/SDLSystem.h"
#include "../ForegroundEclipseEngine/GameElements/Scene.h"
#include "../ForegroundEclipseEngine/EngineSystem/SDLSystem/SDLMeshComponent.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

// 03. SDL ������ �ε� & �簢��, �̹��� ���

int main(int argv, char** args) {

	// --------------- ���� ���� ----------------

	// SDL �ý��� �ε�
	EngineSystem* engineSystem = new SDLSystem("03. EngineWithOpenGL");
	engineSystem->BuildSystem();

	//// --------------- ���� ��� ���� ----------------

	// �� ����
	Scene* scene = new Scene();
	// ��Ʈ ������ ����
	engineSystem->SetRootScene(scene);

	// ���� ������Ʈ ����
	GameObject* test = new GameObject("test");
	GameObject* unfilledrect = new GameObject("unfilledrect");
	GameObject* filledrect = new GameObject("filledrect");
	GameObject* texturedrect = new GameObject("texturedrect");
	//scene->SetThisComponentToSceneCamera(newCamera);
	scene->AddGameObject(test);
	scene->AddGameObject(unfilledrect);
	scene->AddGameObject(filledrect);
	// ��� ���� �׽�Ʈ
	// �̵� �� �ڽ��� ���̰ų� �ڽ��� ���̰� �̵��ϰų� ��� ó���ǵ��� ����
	
	test->Translate(glm::vec3(50.0f, 50.0f, 0.0f));
	test->AddChild(texturedrect);

	// �Ž� ����

	// ���� �� �簢��
	SDLMeshComponent* unfilledrectMesh = new SDLMeshComponent(100, 100, 0, 0, 0, 255);
	unfilledrect->AddComponent<SDLMeshComponent>(unfilledrectMesh);
	unfilledrect->Translate(glm::vec3(200.0f, 200.0f, 0.f));

	// ���� ���ִ� �簢��
	SDLMeshComponent* filledrectMesh = new SDLMeshComponent(100, 100, 128, 128, 128, 255,true);
	filledrect->AddComponent<SDLMeshComponent>(filledrectMesh);
	filledrect->Translate(glm::vec3(300.0f, 200.0f , 0.f));

	// ���� ���ִ� �簢��
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/image/test.png";
	SDLMeshComponent* texturedMesh = new SDLMeshComponent(parentDir + modelPath);
	texturedrect->AddComponent<SDLMeshComponent>(texturedMesh);
	//texturedrect->Translate(glm::vec3(400.0f, 200.0f, 0.f));

	// --------------- ���� ���� ----------------
	engineSystem->Run();

	// --------------- ���� ----------------

	return 0;
}
