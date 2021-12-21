#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "GameManager.h"
#include "SystemBase/EngineSystem.h"
#include "SystemBase/SDLSystem.h"
#include "SystemBase/glSystem.h"
#include "../GameElements/Component.h"
#include "../Components/Transform.h"
#include "../Components/glCameraComponent.h"
#include "../Utilities/StringConverter.h"
#include "../Utilities/xml/tinyxml.h"

GameManager* GameManager::s_pInstance = 0;
GameManager::GameManager()
{
	// �⺻ ������ ũ��
	windowWidth = 800;
	windowHeight = 600;
}
EngineSystem* GameManager::QueryEngineType(std::string EngineType)
{
	if (EngineType == "SDL") {
		this->engineType = EngineType;
		currentEngine = new SDLSystem();
		return currentEngine;
	}
	else if (EngineType == "GL") {
		this->engineType = EngineType;
		currentEngine = new glSystem();
		return currentEngine;
	}
	return nullptr;
}
GameManager::~GameManager()
{
}

GameManager* GameManager::Instance()
{
	if (s_pInstance == NULL) {
		s_pInstance = new GameManager();
	}
	return s_pInstance;
}

EngineSystem* GameManager::LoadEngineSystemByConfig()
{
	// ���� ���� ��ġ
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	// ���� ��Ʈ ��ȯ
	std::string strFolderPath = SC::TCHARToString(chFilePath);
	std::string currentFolderPath = SC::TrimStringAfterWord(strFolderPath, '\\');

	// confing.ini���� ���� �޾ƿ���
	std::ifstream configInfo(currentFolderPath + "config.ini");
	if (!configInfo.is_open()) {
		std::cerr << "Error: " << strerror(errno);
		exit(1);
		return nullptr;
	}
	else {
		std::string line;
		int offset;
		while (!configInfo.eof())
		{
			getline(configInfo, line);
			if ((offset = line.find("[GameFileRoot]", 0)) != std::string::npos)
			{
				getline(configInfo, line);
				ProjectFolderPath = line;
				ProjectPrimalFilePath = ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal";
				std::cout << ProjectFolderPath << std::endl;
			}
		}
		configInfo.close();
	}

	// ���� Ÿ�� ���
	std::string EngineType;
	std::ifstream engineTypeInfo(ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal");
	std::string temp = ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal";
	if (!engineTypeInfo.is_open()) {
		std::cerr << "Error: " << strerror(errno);
		exit(1);
		return nullptr;
	}
	else {
		// ���� Ÿ�� ��������
		TiXmlDocument ReadDoc;
		ReadDoc.LoadFile(ProjectPrimalFilePath.c_str());
		TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("Game");
		TiXmlElement* sub = ReadRoot->FirstChildElement("EngineType");
		std::cout << sub->GetText() << std::endl;
		EngineType = sub->GetText();

		engineTypeInfo.close();
	}
	gameName = SC::GetProjectName(ProjectFolderPath);
	return QueryEngineType(EngineType);
}

void GameManager::ApplySettingsInConfig()
{
	// ���� �ε�
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile(ProjectPrimalFilePath.c_str());

	// ��Ʈ ���
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("Game");

	// �� ����Ʈ
	TiXmlElement* scenes = ReadRoot->FirstChildElement("Scenes");

	// �� ��� ��������
	TiXmlHandle hscene(0);
	hscene = TiXmlHandle(scenes);
	TiXmlElement* scene = hscene.FirstChildElement().Element();

	// �� ������Ʈ���� ���� ������ ����ϴ� ����� ���� �߰����� �ʾƼ�
	// ���� �ϳ��� ����ϱ�� �����Ƿ� �ϴ� ���� ���̶�� ����

	if (scene != NULL) {
		Scene* AddScene = new Scene();
		this->GetCurrentEngine()->SetRootScene(AddScene);
	}
	else {
		// ���� �ϳ��� ������ ���� ��ƼƼ�� ����
		return;
	}

	// ���� ��ƼƼ ��� ��������
	TiXmlElement* gameentities = scene->FirstChildElement("GameEntities");

	// ���� ��ƼƼ ��ȸ�ϱ�
	TiXmlElement* gameentityName;

	TiXmlHandle hgameentity(0);
	hgameentity = TiXmlHandle(gameentities);
	TiXmlElement* gameentity;
	for (
		gameentity = hgameentity.FirstChildElement().Element();
		gameentity != NULL;
		gameentity = gameentity->NextSiblingElement()
		)
	{
		gameentityName = gameentity->FirstChildElement("a:Name");
		GameObject* AddEntity = new GameObject(gameentityName->GetText());

		// ������Ʈ ��� ��������
		TiXmlElement* components = gameentity->FirstChildElement();
		TiXmlHandle hcomponent(0);
		hcomponent = TiXmlHandle(components);

		//������Ʈ ��ȸ
		TiXmlElement* component;
		for (
			component = hcomponent.FirstChildElement().Element();
			component != NULL;
			component = component->NextSiblingElement()
			)
		{
			TiXmlAttribute* pAttrib;
			pAttrib = component->LastAttribute();
			QueryComponentType(pAttrib->Value(), AddEntity);
		}
	}
}

void GameManager::QueryComponentType(std::string name, GameObject* target)
{
	if (name == "a:Camera")
		if (this->GetEngineType() == "GL") {
			glCameraComponent* temp = new glCameraComponent(800, 600, glm::vec3(0.0f, 0.0f, 0.0f));
			target->AddComponent< glCameraComponent>(temp);
			dynamic_cast<glSystem*>(this->GetCurrentEngine())->GetSceneRoot()->SetThisComponentToSceneCamera(temp);
		}
}

EngineSystem* GameManager::GetCurrentEngine()
{
	return currentEngine;
}

std::string GameManager::GetGameName()
{
	return gameName;
}
unsigned int GameManager::IssuingNewID()
{
	return IDCount++;
}