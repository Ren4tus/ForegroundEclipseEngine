#include <iostream>
#include <fstream>
#include <stdio.h>
#include "SDLSystem.h"
#include "Renderer.h"
#include "SDLSystem/SDLRenderCore.h"
#include "SDLSystem/SDLInputCore.h"
SDLSystem::SDLSystem()
{
	EngineType = "SDL";

	//inputCore = new SDLInputCore();
	//EngineRenderer = std::make_shared<Renderer>();
}
bool SDLSystem::BuildSystem()
{
	//EngineRenderer->currentEngine = this;
	SystemInit();
	return false;
}

bool SDLSystem::SystemInit()
{
	//FILE* fp = 0;
	//char buf[256];
	//fp = fopen("E:\\DEV\\ForegroundEclipseEngine_Solution\\x64\\Debug\\confing.txt","r");
	//std::cout << fgetc(fp);

	//std::fstream configInfo;
	//configInfo.open("E:\\DEV\\ForegroundEclipseEngine_Solution\\x64\\Debug\\confing.txt");
	//if (!configInfo.is_open()) {
	//	std::cerr << "Error: " << strerror(errno);
	//	//TODO: 프로그램 종료되게 하기
	//	
	//}
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		g_pWindow = SDL_CreateWindow(
			"TestWindow",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640, 480, SDL_WINDOW_SHOWN
		);
		if (g_pWindow != 0) {
			renderCore = new SDLRenderCore();
			(dynamic_cast<SDLRenderCore*>(renderCore))->renderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			//g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
		else {
			return 1;
		}
	}

	SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetRenderer());
	SDL_Delay(5000);
	SDL_Quit();
	return false;
}

SDL_Renderer* SDLSystem::GetRenderer()
{
	return nullptr;
	return (dynamic_cast<SDLRenderCore*>(renderCore))->renderer;
}
