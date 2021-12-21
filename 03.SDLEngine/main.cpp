#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/SDLSystem.h"
#include "../ForegroundEclipseEngine/GameElements/Scene.h"
#include "../ForegroundEclipseEngine/EngineSystem/SDLSystem/SDLMeshComponent.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

// 03. SDL 윈도우 로드 & 사각형, 이미지 출력

int main(int argv, char** args) {

	// --------------- 엔진 설정 ----------------

	// SDL 시스템 로드
	EngineSystem* engineSystem = new SDLSystem("03. EngineWithOpenGL");
	engineSystem->BuildSystem();

	//// --------------- 게임 요소 설정 ----------------

	// 씬 생성
	Scene* scene = new Scene();
	// 루트 씬으로 설정
	engineSystem->SetRootScene(scene);

	// 게임 오브젝트 생성
	GameObject* test = new GameObject("test");
	GameObject* unfilledrect = new GameObject("unfilledrect");
	GameObject* filledrect = new GameObject("filledrect");
	GameObject* texturedrect = new GameObject("texturedrect");
	//scene->SetThisComponentToSceneCamera(newCamera);
	scene->AddGameObject(test);
	scene->AddGameObject(unfilledrect);
	scene->AddGameObject(filledrect);
	// 행렬 전파 테스트
	// 이동 후 자식을 붙이거나 자식을 붙이고 이동하거나 모두 처리되도록 구현
	
	test->Translate(glm::vec3(50.0f, 50.0f, 0.0f));
	test->AddChild(texturedrect);

	// 매쉬 생성

	// 속이 빈 사각형
	SDLMeshComponent* unfilledrectMesh = new SDLMeshComponent(100, 100, 0, 0, 0, 255);
	unfilledrect->AddComponent<SDLMeshComponent>(unfilledrectMesh);
	unfilledrect->Translate(glm::vec3(200.0f, 200.0f, 0.f));

	// 속이 차있는 사각형
	SDLMeshComponent* filledrectMesh = new SDLMeshComponent(100, 100, 128, 128, 128, 255,true);
	filledrect->AddComponent<SDLMeshComponent>(filledrectMesh);
	filledrect->Translate(glm::vec3(300.0f, 200.0f , 0.f));

	// 속이 차있는 사각형
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/image/test.png";
	SDLMeshComponent* texturedMesh = new SDLMeshComponent(parentDir + modelPath);
	texturedrect->AddComponent<SDLMeshComponent>(texturedMesh);
	//texturedrect->Translate(glm::vec3(400.0f, 200.0f, 0.f));

	// --------------- 게임 진행 ----------------
	engineSystem->Run();

	// --------------- 종료 ----------------

	return 0;
}
