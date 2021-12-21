#include "Scene.h"
#include <iostream>
#include "../EngineSystem/GameManager.h"
#include "../EngineSystem/SystemBase/glSystem.h"
#include "../Components/glCameraComponent.h"
#include "GameObject.h"
#include "../Utilities/glTime.h"
#include "Component.h"
#include "../Components/Transform.h"
#include "../Utilities/Time.h"
Scene::Scene()
{
	m_IsGameEnd = false;
}
Scene::Scene(std::string name)
{
	m_name = name;
}
Scene::~Scene()
{
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		delete (*iter);
	}
}
void Scene::Awake()
{
}
void Scene::Start()
{
	// ----------- Awake -----------

	// ������Ʈ, ������Ʈ�� ���� ID �Ҵ� ����.
	// On, Off ������� ����

	for (
		std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++
		)
	{
		(*iter)->Awake();
	}

	// ----------- Start -----------

	// On ���¿� ���ؼ��� ����
	for (
		std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++
		)
	{
		(*iter)->Start();
	}
}
void Scene::Run()
{
	// ----------- ��� ���� -----------

	// ���� �� �θ� ������Ʈ�� �ٲ�ų� ���ŵ� ���� �ֱ� ������ ������ǥ �����
	// �̺�Ʈ�� ó���ϰų� �Ź� �����ؾ� �ϴµ� ���⼱ �Ź� �����ϱ�� ��.

	// ���� ��ǥ ���� �ʱ�ȭ
	ResetGameObjectWorldPosition();
	// �θ� ��(null)�� ���ӿ�����Ʈ��κ��� ��� ���� ����
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		if ((*iter)->GetParent() == nullptr) {
			(*iter)->MatrixPropagation();
			// �ֻ��� ���ӿ�����Ʈ���� ���� ��ǥ�� �ڽ��� ��ǥ��
			(*iter)->m_worldPosition = (*iter)->GetTransform()->m_position;
			(*iter)->m_worldRotate = (*iter)->GetTransform()->m_rotation;
			(*iter)->m_worldScale = (*iter)->GetTransform()->m_scale;
		}
	}

	// ----------- Update -----------
	std::cout << "non-fixed" << std::endl;
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		(*iter)->Update();
	}

	// ----------- FixedUpdate -----------

	//GL or SDL�� ���� �ٸ��� ó��
	if (
		(GM::Instance()->GetEngineType() == "GL" && glTimer.DeltaTime >= glTimer.frame) ||
		(GM::Instance()->GetEngineType() == "SDL" && SDLTimer.DeltaTime >= SDLTimer.frame)
		)
	{
		std::cout << "fixed" << std::endl;
		for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
			iter != m_ManagedGameObjects.end();
			iter++)
		{
			(*iter)->FixedUpdate();
		}
	}
}

void Scene::Render()
{
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		if (GM::Instance()->GetEngineType() == "GL") {
			// ������ �Ž��鿡�� directLight & camera�� ������ ����
			glCameraComponent* tempGlCamera = dynamic_cast<glCameraComponent*>(cameraComponent);
			glMeshComponent* mesh = (*iter)->GetComponent<glMeshComponent>();
			if (mesh != nullptr) {
				mesh->SetDrawInfo(*directLightShader, (*tempGlCamera));
			}
		}
		(*iter)->Render();
	}
}

void Scene::AddGameObject(GameObject* GO)
{
	m_ManagedGameObjects.push_back(GO);
	GO->ownerScene = this;
}

void Scene::ResetGameObjectWorldPosition()
{
	for (std::vector<GameObject*>::iterator iter = m_ManagedGameObjects.begin();
		iter != m_ManagedGameObjects.end();
		iter++)
	{
		(*iter)->m_worldPosition = (*iter)->GetTransform()->m_position;
		(*iter)->m_worldRotate = (*iter)->GetTransform()->m_rotation;
		(*iter)->m_worldScale = (*iter)->GetTransform()->m_scale;
	}
}

void Scene::SetThisComponentToSceneCamera(Component* cameraComp)
{
	this->cameraComponent = cameraComp;

	//OpenGL�� ���
	if (
		dynamic_cast<glSystem*>(GM::Instance()->GetCurrentEngine()) != NULL
		&& dynamic_cast<glCameraComponent*>(cameraComponent) != NULL
		)
	{
		dynamic_cast<glCameraComponent*>(cameraComponent)->SetWindow(dynamic_cast<glSystem*>(GM::Instance()->GetCurrentEngine())->GetWindow());
	}
}

glCameraComponent* Scene::GetGLSceneCamera()
{
	try {
		return dynamic_cast<glCameraComponent*>(cameraComponent);
	}
	catch (const std::exception& e) {
		std::cout << "There's no glCamera." << e.what() << std::endl;
	}
}

bool Scene::SetSkyBox(Shader& shader, std::string FolderPath)
{
	float skyboxVertices2[] =
	{
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f
	};

	unsigned int skyboxIndices2[] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};
	if ((dynamic_cast<glSystem*>(GM::Instance()->GetCurrentEngine())) == NULL) {
		return false;
	}
	skyboxShader = &shader;
	skyboxShader->Activate();
	glUniform1i(glGetUniformLocation(skyboxShader->ID, "skybox"), 0);
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices2), &skyboxVertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices2), &skyboxIndices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string facesCubemap[6] =
	{
		FolderPath + "/right.jpg",
		FolderPath + "/left.jpg",
		FolderPath + "/top.jpg",
		FolderPath + "/bottom.jpg",
		FolderPath + "/front.jpg",
		FolderPath + "/back.jpg"
	};

	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}
}

bool Scene::DrawSkyBox()
{
	if (skyboxShader == NULL)
		return false;

	skyboxShader->Activate();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glCameraComponent* glCamera = dynamic_cast<glCameraComponent*>(cameraComponent);
	view = glm::mat4(glm::mat3(glm::lookAt(glCamera->Position, glCamera->Position + glCamera->Orientation, glCamera->Up)));
	projection = glm::perspective(glm::radians(45.0f), (float)(GM::Instance()->getWindowWidth() / GM::Instance()->getWindowHeight()), 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	return true;
}

bool Scene::SetDirectionalLight(Shader& shader)
{
	directLightShader = &shader;
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	shader.Activate();
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	return true;
}