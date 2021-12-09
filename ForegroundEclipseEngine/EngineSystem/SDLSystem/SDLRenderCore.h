#pragma once
#include <SDL.h>
#include "../IEngineRendererCore.h"
class SDLRenderCore : public IEngineRendererCore
{
public:
	SDLRenderCore();
	~SDLRenderCore();
public:
	SDL_Renderer* renderer;
public:
	virtual void RenderAllObject() override;
};
