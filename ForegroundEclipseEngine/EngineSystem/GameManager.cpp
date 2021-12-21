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
	// 기본 윈도우 크기
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
	// 현재 폴더 위치
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	// 폴더 루트 변환
	std::string strFolderPath = SC::TCHARToString(chFilePath);
	std::string currentFolderPath = SC::TrimStringAfterWord(strFolderPath, '\\');

	// confing.ini에서 설정 받아오기
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

	// 엔진 타입 계산
	std::string EngineType;
	std::ifstream engineTypeInfo(ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal");
	std::string temp = ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal";
	if (!engineTypeInfo.is_open()) {
		std::cerr << "Error: " << strerror(errno);
		exit(1);
		return nullptr;
	}
	else {
		// 엔진 타입 가져오기
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
	// 문서 로드
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile(ProjectPrimalFilePath.c_str());

	// 루트 노드
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("Game");

	// 씬 리스트
	TiXmlElement* scenes = ReadRoot->FirstChildElement("Scenes");

	// 씬 목록 가져오기
	TiXmlHandle hscene(0);
	hscene = TiXmlHandle(scenes);
	TiXmlElement* scene = hscene.FirstChildElement().Element();

	// 이 프로젝트에선 씬을 여러개 사용하는 기능을 아직 추가하지 않아서
	// 씬을 하나만 사용하기로 했으므로 일단 단일 씬이라고 가정

	if (scene != NULL) {
		Scene* AddScene = new Scene();
		this->GetCurrentEngine()->SetRootScene(AddScene);
	}
	else {
		// 씬이 하나도 없으면 게임 엔티티도 없음
		return;
	}

	// 게임 엔티티 목록 가져오기
	TiXmlElement* gameentities = scene->FirstChildElement("GameEntities");

	// 게임 엔티티 순회하기
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

		// 컴포넌트 목록 가져오기
		TiXmlElement* components = gameentity->FirstChildElement();
		TiXmlHandle hcomponent(0);
		hcomponent = TiXmlHandle(components);

		//컴포넌트 순회
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