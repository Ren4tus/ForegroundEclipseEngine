#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "GameManager.h"
#include "EngineSystem.h"
#include "SDLSystem.h"
#include "../Utilities/StringConverter.h"
GameManager* GameManager::s_pInstance = 0;
GameManager::GameManager()
{

}
EngineSystem* GameManager::QueryEngineType(std::string EngineType)
{
	if (EngineType == "SDL"){
		return new SDLSystem();
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
	
	TCHAR chFilePath[256] = { 0, };
	GetModuleFileName(NULL, chFilePath, 256);

	std::string strFolderPath = SC::TCHARToString(chFilePath);
	std::string currentFolderPath = SC::TrimStringAfterWord(strFolderPath, '\\');
	
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
				std::cout << ProjectFolderPath << std::endl;
			}
		}
		configInfo.close();
	}
	std::string EngineType;
	std::ifstream engineTypeInfo(ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal");
	std::string temp = ProjectFolderPath + SC::GetProjectName(ProjectFolderPath) + ".primal";
	if (!engineTypeInfo.is_open()) {
		std::cerr << "Error: " << strerror(errno);
		exit(1);
		return nullptr;
	}
	else {
		std::string textString;
		getline(engineTypeInfo, textString);
		int firstAdress = textString.find("<EngineType>") + std::string("<EngineType>").size();
		int secondAdress = textString.find("</EngineType>");
		EngineType = textString.substr(firstAdress , secondAdress - firstAdress);

		engineTypeInfo.close();
	}
	
	return QueryEngineType(EngineType);
}
