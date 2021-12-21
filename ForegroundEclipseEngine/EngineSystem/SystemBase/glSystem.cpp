#include <SDL.h>
#include <iomanip>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include "glSystem.h"

#include "../glSystem/VAO.h"
#include "../glSystem/VBO.h"
#include "../glSystem/EBO.h"
#include "../glSystem/Texture.h"
#include "../glSystem/Shaders/shaderClass.h"
#include "../GameManager.h"
#include "../../GameElements/GameObject.h"
#include "../../GameElements/Component.h"
#include "../../GameElements/Scene.h"
#include "../../pch.h"
#include "../../Utilities/Time.h"
#include "../../Utilities/glTime.h"
#include "../../Utilities/StringConverter.h"
#include "../../Components/Transform.h"
#include "../../Components/glCameraComponent.h"



glSystem::glSystem() : run(true), window(NULL) 
{
	GM::Instance()->SetGameName("DefaultGameName");
	EngineType = "GL";
	GM::Instance()->SetEngineType("GL");
	GM::Instance()->SetCurrentEngine(this);
}

glSystem::glSystem(std::string GameName) : run(true), window(NULL)
{
	GM::Instance()->SetGameName(GameName);
	EngineType = "GL";
	GM::Instance()->SetEngineType("GL");
	GM::Instance()->SetCurrentEngine(this);
}

glSystem::~glSystem() {
	// Run 안에도 있지만 혹시 모르니 확실하게 할당 해제
	glfwDestroyWindow(window);
	glfwTerminate();
	
}

bool glSystem::BuildSystem()
{
	SystemInit();

	return true;
}

bool glSystem::SystemInit()
{
	// GLFW 초기화
	glfwInit();

	// GLFW 버전 정의
	// OpenGL 3.3 사용
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// GLFW CORE profile 정의
	// TODO: 뭔지 잘 몰라서 나중에 제대로 알아보기
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window 생성
	window = glfwCreateWindow(GM::Instance()->getWindowWidth(), GM::Instance()->getWindowHeight(), (GM::Instance()->GetGameName()).c_str(), NULL, NULL);
	// 에러 체크
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD 로드
	gladLoadGL();
	// 뷰포트 화면 전체로
	glViewport(0, 0, GM::Instance()->getWindowWidth(), GM::Instance()->getWindowHeight());

	// Depth Buffer 켜기
	glEnable(GL_DEPTH_TEST);

	// 페이스 컬링 켜기
	glEnable(GL_CULL_FACE);
	// 페이스 컬링 front로
	glCullFace(GL_FRONT);
	// ccw로 설정
	glFrontFace(GL_CCW);

}

bool glSystem::Run()
{
	// FPS 표시 및 시간 체크에 사용되는 변수
	glTimer.prevTime = 0.0;
	glTimer.crntTime = 0.0;
	// 프레임 추적을 위해 사용되는 변수
	glTimer.counter = 0;

	// Awake, Start
	this->GetSceneRoot()->Start();

	// 메인 루프
	while (!glfwWindowShouldClose(window))
	{
		// 카운터와 시간을 갱신
		glTimer.crntTime = glfwGetTime();
		glTimer.DeltaTime = glTimer.crntTime - glTimer.prevTime;
		glTimer.counter++;
		if (glTimer.DeltaTime >= glTimer.frame)
		{
			if (bDisplayFPS) {
				// 제목 갱신
				std::stringstream stream;
				stream << std::fixed << std::setprecision(1) << (1.0 / glTimer.DeltaTime) * glTimer.counter;
				std::string FPS = stream.str();
				std::stringstream stream2;
				stream2 << std::fixed << std::setprecision(1) << (glTimer.DeltaTime / glTimer.counter) * 1000;
				std::string ms = stream2.str();
				std::string newTitle = GM::Instance()->GetGameName() + " " + FPS + "FPS / " + ms + "ms";
				glfwSetWindowTitle(window, newTitle.c_str());
			}

			// 타이머와 카운터를 리셋
			glTimer.prevTime = glTimer.crntTime;
			glTimer.counter = 0;
		}

		// 배경색을 정의
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back buffer와 depth buffer를 비움
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 씬이 가지고있는 게임오브젝트들의 업데이트
		try
		{
			this->GetSceneRoot()->Run();
		}
		catch (const std::exception&)
		{
			std::cout << "No Scene Detected." << std::endl;
			glfwDestroyWindow(window);
			glfwTerminate();
			return false;
		}

		//dynamic cast가 비용이 높은 연산이라 한번만 수행하고 레퍼런스를 저장
		if (camera == nullptr) {
			try
			{
				camera = dynamic_cast<glCameraComponent*>(this->GetSceneRoot()->GetGLSceneCamera());
			}
			catch (const std::exception&)
			{
				std::cout << "No CameraComponent Detected." << std::endl;
				glfwDestroyWindow(window);
				glfwTerminate();
				return false;
			}
		}

		// 카메라 업데이트, input(use 인 경우)
		camera->Inputs();
		camera->updateMatrix(45.0f, 0.1f, 300.0f);
		
		// 게임 오브젝트들의 렌더링 (가지고 있는 mesh 기반으로)
		this->GetSceneRoot()->Render();
		
		// 큐브맵(skybox)을 위한 depth 설정
		glDepthFunc(GL_LEQUAL);

		this->GetSceneRoot()->DrawSkyBox();

		// 원래 depth로 전환
		glDepthFunc(GL_LESS);

		// 백버퍼 프론트버퍼 전환
		glfwSwapBuffers(window);
		// GLFW events 처리
		glfwPollEvents();
	}

	// 윈도우 해제
	glfwDestroyWindow(window);
	// GLFW 해제
	glfwTerminate();
	return 0;
}

Scene* glSystem::GetSceneRoot()
{
	return gameScene;
}

void glSystem::SetRootScene(Scene* scene)
{
	this->gameScene = scene;
}