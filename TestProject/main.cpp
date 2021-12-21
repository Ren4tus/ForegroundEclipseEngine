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

	// --------------- ���� ���� ----------------

	// Config.ini�κ��� �ڵ����� ���� ����
	// NOTE : exe ������ �����ϴ� ��ġ�� config.ini�� �־�� �� 
	// NOTE : �� ���������� �����ͷ� ���� ī�޶� ������ ���� ������Ʈ�� ������ ����
	// NOTE : ������Ʈ �̸��� ������� ������ ã�⶧���� �����ͷ� ������ �� ������Ʈ �̸��� "02. GL_Skybox" ��Ȯ�ϰ� �������� ��
	EngineSystem* engineSystem = GM::Instance()->LoadEngineSystemByConfig();
	// ���� config�� ������� �ʴ´ٸ� �Ʒ� �ڵ带 ��� �̿�
	//EngineSystem* engineSystem = new glSystem();
	engineSystem->BuildSystem();

	// --------------- ���� ��� ���� ----------------
	
	// confing ���Ϸκ��� �����ͷ� �۾��� scene, (camera ������Ʈ ���Ե�)gameobject�� �ε�
	GM::Instance()->ApplySettingsInConfig();

	// �� ���� 
	 
	// --------------- ���� config�� ������� �ʴ´ٸ� �Ʒ� �ڵ带 ��� �̿� ----------------
	//Scene* scene = new Scene();
	//engineSystem->SetRootScene(scene);
	// -----------------------------------------------------------------------------------
	
	// ���� ������Ʈ ����
	GameObject* test = new GameObject();

	// �Ž� ����
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/Resources/models/airplane/scene.gltf";
	glMeshComponent* newmesh = new glMeshComponent((parentDir + modelPath).c_str());
	test->AddComponent<glMeshComponent>(newmesh);
	engineSystem->GetSceneRoot()->AddGameObject(test);

	// --------------- ���� config�� ������� �ʴ´ٸ� �Ʒ� �ڵ带 ��� �̿� ----------------
	//glCameraComponent* newCamera = new glCameraComponent(800, 600, glm::vec3(0.0f, 0.0f, 0.0f));
	//engineSystem->GetSceneRoot()->SetThisComponentToSceneCamera(newCamera);
	// -----------------------------------------------------------------------------------
	
	std::string directVertPath = (parentDir + "Resources/default.vert").c_str();
	// directLight�� skybox�� Shader ����
	Shader directLight((parentDir + "/Resources/default.vert").c_str(), (parentDir + "/Resources/default.frag").c_str());
	Shader mainSkyboxShader((parentDir + "/Resources/skybox.vert").c_str(), (parentDir + "/Resources/skybox.frag").c_str());
	engineSystem->GetSceneRoot()->SetDirectionalLight(directLight);

	// ������ �Ž��鿡�� directLight & camera�� ������ ����
	newmesh->SetDrawInfo(directLight, (*(engineSystem->GetSceneRoot()->GetGLSceneCamera())));

	// skybox �ε� & ���� ���� skybox ����
	std::string skyBoxDir = parentDir + "/Resources/skybox";
	engineSystem->GetSceneRoot()->SetSkyBox(mainSkyboxShader, skyBoxDir);

	// --------------- ���� ���� ----------------
	engineSystem->Run();

	// --------------- ���� ----------------
	// ������ ���̴� �Ҵ� ����
	directLight.Delete();
	mainSkyboxShader.Delete();

	// �� ���� (���� �������ִ� ���� ������Ʈ�� ������Ʈ ������)
	delete engineSystem->GetSceneRoot();

	// ���� �ý��� ����
	delete engineSystem;

	return 0;
}
