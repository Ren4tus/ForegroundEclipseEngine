#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cassert>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "SDLSystem.h"
#include "../SDLSystem/SDLInputHandler.h"
#include "../GameManager.h"
#include "../../GameElements/Scene.h"
#include "../../Utilities/Time.h"
SDLSystem::SDLSystem()
{
	EngineType = "SDL";
	GM::Instance()->SetEngineType("SDL");
	GM::Instance()->SetCurrentEngine(this);
}
SDLSystem::SDLSystem(std::string name)
{
	EngineType = "SDL";
	GM::Instance()->SetEngineType("SDL");
	GM::Instance()->SetCurrentEngine(this);
	GM::Instance()->SetGameName(name);
}
SDLSystem::~SDLSystem()
{
}
bool SDLSystem::BuildSystem()
{
	SystemInit();
	return false;
}

bool SDLSystem::SystemInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		m_pWindow = SDL_CreateWindow(
			GM::Instance()->GetGameName().c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			GM::Instance()->getWindowWidth(), GM::Instance()->getWindowWidth(), SDL_WINDOW_SHOWN
		);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
			//SDL_Mixer 초기화
			if (SDL_Init(SDL_INIT_AUDIO) < 0) {
				std::cout << ("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			}
		}
		else {
			return 1;
		}
	}

	return false;
}

bool SDLSystem::Run()
{
	// FPS 표시 및 시간 체크에 사용되는 변수
	SDLTimer.prevTime = 0.0;
	SDLTimer.crntTime = 0.0;
	// 프레임 추적을 위해 사용되는 변수
	SDLTimer.counter = 0;

	// Awake, Start
	this->GetSceneRoot()->Start();

	while (!bGameEnd) {
		// 카운터와 시간을 갱신
		SDLTimer.crntTime = SDL_GetTicks() / 1000.0f;
		SDLTimer.DeltaTime = SDLTimer.crntTime - SDLTimer.prevTime;
		SDLTimer.counter++;

		if (SDLTimer.DeltaTime >= SDLTimer.frame)
		{
			if (bDisplayFPS) {
				// 제목 갱신
				std::stringstream stream;
				stream << std::fixed << std::setprecision(1) << (1.0 / SDLTimer.DeltaTime) * SDLTimer.counter;
				std::string FPS = stream.str();
				std::stringstream stream2;
				stream2 << std::fixed << std::setprecision(1) << (SDLTimer.DeltaTime / SDLTimer.counter) * 1000;
				std::string ms = stream2.str();
				std::string newTitle = GM::Instance()->GetGameName() + " " + FPS + "FPS / " + ms + "ms";
				SDL_SetWindowTitle(m_pWindow, newTitle.c_str());
			}

			// 타이머와 카운터를 리셋
			SDLTimer.prevTime = SDLTimer.crntTime;
			SDLTimer.counter = 0;
		}
		handleEvnets();

		// 씬이 가지고있는 게임오브젝트들의 업데이트
		try
		{
			this->GetSceneRoot()->Run();
		}
		catch (const std::exception&)
		{
			std::cout << "No Scene Detected." << std::endl;
			clean();
			return false;
		}
		SDL_SetRenderDrawColor(m_pRenderer, 178, 204, 255, 255);
		// 화면 초기화
		SDL_RenderClear(m_pRenderer);
		// 게임 오브젝트들의 렌더링 (가지고 있는 mesh 기반으로)
		this->GetSceneRoot()->Render();
		// 렌더링 요청 수행
		SDL_RenderPresent(m_pRenderer);
	}
	clean();
	return true;
}

Scene* SDLSystem::GetSceneRoot()
{
	return gameScene;
}

void SDLSystem::SetRootScene(Scene* scene)
{
	this->gameScene = scene;
}

void SDLSystem::handleEvnets()
{
	TheInputHandler::Instance()->update();
}

void SDLSystem::clean()
{
	SDLInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	//sdl image 종료
	IMG_Quit();
	//sdl 종료
	SDL_Quit();
	bGameEnd = true;
}