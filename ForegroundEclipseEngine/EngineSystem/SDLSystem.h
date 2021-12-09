#pragma once
#include <SDL.h>
#include "EngineSystem.h"
class IEngineRendererCore;

class SDLSystem : public EngineSystem
{
public:
	SDLSystem();

	~SDLSystem()
	{
	}

private:
	virtual bool BuildSystem() override;
	virtual bool SystemInit() override;
	SDL_Window* g_pWindow = 0;
	SDL_Renderer* renderer;
public:
	SDL_Renderer* GetRenderer();
};
