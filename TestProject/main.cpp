#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/SDLSystem.h"
#include "../ForegroundEclipseEngine/EngineSystem/SystemBase/glSystem.h"
#include "../ForegroundEclipseEngine/EngineSystem/GameManager.h"
#include "../ForegroundEclipseEngine/GameElements/Scene.h"
#include "../ForegroundEclipseEngine/GameElements/GameObject.h"
#include "../ForegroundEclipseEngine/pch.h"
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

int main(int argv, char** args){

	// --------------- 엔진 설정 ----------------

	// Config.ini로부터 자동으로 엔진 생성
	// NOTE : exe 파일이 존재하는 위치에 config.ini가 있어야 함 
	// NOTE : 이 예제에서는 에디터로 씬과 카메라가 부착된 게임 오브젝트를 생성한 상태
	// NOTE : 프로젝트 이름을 기반으로 파일을 찾기때문에 에디터로 생성할 때 프로젝트 이름을 "02. GL_Skybox" 정확하게 만들어줘야 함
	EngineSystem* engineSystem = GM::Instance()->LoadEngineSystemByConfig();
	// 만약 config를 사용하지 않는다면 아래 코드를 대신 이용
	//EngineSystem* engineSystem = new glSystem();
	engineSystem->BuildSystem();

	// --------------- 게임 요소 설정 ----------------
	
	// confing 파일로부터 에디터로 작업한 scene, (camera 컴포넌트 포함된)gameobject을 로드
	GM::Instance()->ApplySettingsInConfig();

	// 씬 생성 
	 
	// --------------- 만약 config를 사용하지 않는다면 아래 코드를 대신 이용 ----------------
	//Scene* scene = new Scene();
	//engineSystem->SetRootScene(scene);
	// -----------------------------------------------------------------------------------
	
	// 게임 오브젝트 생성
	GameObject* test = new GameObject();

	// 매쉬 생성
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/models/airplane/scene.gltf";
	glMeshComponent* newmesh = new glMeshComponent((parentDir + modelPath).c_str());
	test->AddComponent<glMeshComponent>(newmesh);
	engineSystem->GetSceneRoot()->AddGameObject(test);

	// --------------- 만약 config를 사용하지 않는다면 아래 코드를 대신 이용 ----------------
	//glCameraComponent* newCamera = new glCameraComponent(800, 600, glm::vec3(0.0f, 0.0f, 0.0f));
	//engineSystem->GetSceneRoot()->SetThisComponentToSceneCamera(newCamera);
	// -----------------------------------------------------------------------------------
	
	std::string directVertPath = (parentDir + "Resources/default.vert").c_str();
	// directLight와 skybox의 Shader 생성
	Shader directLight((parentDir + "/Resources/default.vert").c_str(), (parentDir + "/Resources/default.frag").c_str());
	Shader mainSkyboxShader((parentDir + "/Resources/skybox.vert").c_str(), (parentDir + "/Resources/skybox.frag").c_str());
	engineSystem->GetSceneRoot()->SetDirectionalLight(directLight);

	// 생성한 매쉬들에게 directLight & camera의 시점을 제공
	newmesh->SetDrawInfo(directLight, (*(engineSystem->GetSceneRoot()->GetGLSceneCamera())));

	// skybox 로드 & 현재 씬에 skybox 적용
	std::string skyBoxDir = parentDir + "/Resources/skybox";
	engineSystem->GetSceneRoot()->SetSkyBox(mainSkyboxShader, skyBoxDir);

	// --------------- 게임 진행 ----------------
	engineSystem->Run();

	// --------------- 종료 ----------------
	// 생성한 쉐이더 할당 해제
	directLight.Delete();
	mainSkyboxShader.Delete();

	// 씬 해제 (씬이 가지고있는 게임 오브젝트와 컴포넌트 해제함)
	delete engineSystem->GetSceneRoot();

	// 엔진 시스템 해제
	delete engineSystem;

	return 0;
}
