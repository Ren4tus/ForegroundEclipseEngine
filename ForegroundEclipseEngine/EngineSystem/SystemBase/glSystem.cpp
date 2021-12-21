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
	// Run �ȿ��� ������ Ȥ�� �𸣴� Ȯ���ϰ� �Ҵ� ����
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
	// GLFW �ʱ�ȭ
	glfwInit();

	// GLFW ���� ����
	// OpenGL 3.3 ���
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// GLFW CORE profile ����
	// TODO: ���� �� ���� ���߿� ����� �˾ƺ���
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window ����
	window = glfwCreateWindow(GM::Instance()->getWindowWidth(), GM::Instance()->getWindowHeight(), (GM::Instance()->GetGameName()).c_str(), NULL, NULL);
	// ���� üũ
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD �ε�
	gladLoadGL();
	// ����Ʈ ȭ�� ��ü��
	glViewport(0, 0, GM::Instance()->getWindowWidth(), GM::Instance()->getWindowHeight());

	// Depth Buffer �ѱ�
	glEnable(GL_DEPTH_TEST);

	// ���̽� �ø� �ѱ�
	glEnable(GL_CULL_FACE);
	// ���̽� �ø� front��
	glCullFace(GL_FRONT);
	// ccw�� ����
	glFrontFace(GL_CCW);

}

bool glSystem::Run()
{
	// FPS ǥ�� �� �ð� üũ�� ���Ǵ� ����
	glTimer.prevTime = 0.0;
	glTimer.crntTime = 0.0;
	// ������ ������ ���� ���Ǵ� ����
	glTimer.counter = 0;

	// Awake, Start
	this->GetSceneRoot()->Start();

	// ���� ����
	while (!glfwWindowShouldClose(window))
	{
		// ī���Ϳ� �ð��� ����
		glTimer.crntTime = glfwGetTime();
		glTimer.DeltaTime = glTimer.crntTime - glTimer.prevTime;
		glTimer.counter++;
		if (glTimer.DeltaTime >= glTimer.frame)
		{
			if (bDisplayFPS) {
				// ���� ����
				std::stringstream stream;
				stream << std::fixed << std::setprecision(1) << (1.0 / glTimer.DeltaTime) * glTimer.counter;
				std::string FPS = stream.str();
				std::stringstream stream2;
				stream2 << std::fixed << std::setprecision(1) << (glTimer.DeltaTime / glTimer.counter) * 1000;
				std::string ms = stream2.str();
				std::string newTitle = GM::Instance()->GetGameName() + " " + FPS + "FPS / " + ms + "ms";
				glfwSetWindowTitle(window, newTitle.c_str());
			}

			// Ÿ�̸ӿ� ī���͸� ����
			glTimer.prevTime = glTimer.crntTime;
			glTimer.counter = 0;
		}

		// ������ ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back buffer�� depth buffer�� ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ���� �������ִ� ���ӿ�����Ʈ���� ������Ʈ
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

		//dynamic cast�� ����� ���� �����̶� �ѹ��� �����ϰ� ���۷����� ����
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

		// ī�޶� ������Ʈ, input(use �� ���)
		camera->Inputs();
		camera->updateMatrix(45.0f, 0.1f, 300.0f);
		
		// ���� ������Ʈ���� ������ (������ �ִ� mesh �������)
		this->GetSceneRoot()->Render();
		
		// ť���(skybox)�� ���� depth ����
		glDepthFunc(GL_LEQUAL);

		this->GetSceneRoot()->DrawSkyBox();

		// ���� depth�� ��ȯ
		glDepthFunc(GL_LESS);

		// ����� ����Ʈ���� ��ȯ
		glfwSwapBuffers(window);
		// GLFW events ó��
		glfwPollEvents();
	}

	// ������ ����
	glfwDestroyWindow(window);
	// GLFW ����
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