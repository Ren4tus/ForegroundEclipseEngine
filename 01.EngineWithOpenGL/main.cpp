#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/glSystem.h"
#include "../ForegroundEclipseEngine/EngineSystem/GameManager.h"
#include "../ForegroundEclipseEngine/GameElements/Scene.h"
#include "../ForegroundEclipseEngine/GameElements/GameObject.h"
#include "../ForegroundEclipseEngine/pch.h"
#include "OrphanMaker.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

// 01. GL 윈도우 로드 & 큐브 출력

int main(int argv, char** args){

	// --------------- 엔진 설정 ----------------
	
	// GL 시스템 로드
	EngineSystem* engineSystem = new glSystem();
	engineSystem->BuildSystem();

	// --------------- 게임 요소 설정 ----------------

	// 씬 생성
	Scene* scene = new Scene();
	// 루트 씬으로 설정
	engineSystem->SetRootScene(scene);

	// 게임 오브젝트 생성
	GameObject* test = new GameObject("parent");
	GameObject* cube = new GameObject("cube");
	GameObject* camera = new GameObject("camera");
	glCameraComponent* newCamera = new glCameraComponent(800, 600, glm::vec3(0.0f, 0.0f, 0.0f));
	scene->SetThisComponentToSceneCamera(newCamera);
	scene->AddGameObject(test);
	scene->AddGameObject(camera);

	// 행렬 전파 테스트
	// 이동 후 자식을 붙이거나 자식을 붙이고 이동하거나 모두 처리되도록 구현
	test->Translate(glm::vec3(0.0f, 5.0f, 0.0f));
	test->AddChild(cube);

	// 부모를 없애는 테스트용 컴포넌트 - R 을 누르면 부모 / 자식 관계 해제
	// 부모에서 떨어져 나와도 자식의 현재 위치가 유지되는지 테스트
	test->AddComponent<OrphanMaker>(new OrphanMaker(test, cube));

	// directLight와 skybox의 Shader 생성
	Shader directLight("default.vert", "default.frag");
	scene->SetDirectionalLight(directLight);

	// 매쉬 생성
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/models/cube/BoxTextured.gltf";
	glMeshComponent* newmesh = new glMeshComponent((parentDir + modelPath).c_str());
	cube->AddComponent<glMeshComponent>(newmesh);

	// --------------- 게임 진행 ----------------
	engineSystem->Run();

	// --------------- 종료 ----------------

	// 생성한 쉐이더 할당 해제
	directLight.Delete();

	// 엔진 시스템 할당 해제
	delete engineSystem;

	return 0;
}
