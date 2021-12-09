#include "../ForegroundEclipseEngine/EngineSystem/SDLSystem.h"
#include "../ForegroundEclipseEngine/EngineSystem/GameManager.h"
#include <iostream>
#include <fstream>
#include <string>
int main(int argv, char** args){
	//std::ifstream configInfo("E:\\DEV\\ForegroundEclipseEngine_Solution\\x64\\Debug\\confing.ini");
	//if (!configInfo.is_open()) {
	//	//TODO: 프로그램 종료되게 하기
	//}
	EngineSystem* engineSystem = GM::Instance()->LoadEngineSystemByConfig();
	engineSystem->BuildSystem();

	return 0;
}
