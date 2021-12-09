#include <iostream>
#include <fstream>
#include <stdio.h>
#include "SDLSystem.h"
#include "Renderer.h"
#include "SDLSystem/SDLRenderCore.h"
#include "SDLSystem/SDLInputCore.h"
#include <cassert>
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
	//	//TODO: ���α׷� ����ǰ� �ϱ�
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
			
			//((SDLRenderCore*)renderCore)->renderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			//assert(dynamic_cast<SDLRenderCore*>(renderCore) == static_cast<SDLRenderCore*>(renderCore));
			//SDLRenderCore*New_pointer = dynamic_cast<SDLRenderCore *>(renderCore);
			//if (NULL != New_pointer)
			//{
			//	New_pointer->renderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			//}
			static_cast<SDLRenderCore*>(renderCore)->renderer = SDL_CreateRenderer(g_pWindow, -1, 0);
				//
			//g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
		else {
			return 1;
		}
	}

	SDL_SetRenderDrawColor(GetRenderer(), 255, 0, 0, 255);
	SDL_RenderClear(GetRenderer());
	SDL_RenderPresent(GetRenderer());
	SDL_Delay(5000);
	SDL_Quit();
	return false;
}

SDL_Renderer* SDLSystem::GetRenderer()
{
	//return nullptr;
	//return ((SDLRenderCore*)renderCore)->renderer;
	return static_cast<SDLRenderCore*>(renderCore)->renderer;
}
