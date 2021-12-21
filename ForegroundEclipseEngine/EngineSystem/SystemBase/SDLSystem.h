#pragma once
#include <SDL.h>
#include "EngineSystem.h"

class Scene;

class SDLSystem : public EngineSystem
{
public:
	SDLSystem();
	SDLSystem(std::string name);
	~SDLSystem();

	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	void clean();

private:
	virtual bool BuildSystem() override;
	virtual bool SystemInit() override;
	virtual bool Run() override;
	virtual Scene* GetSceneRoot() override;
	virtual void SetRootScene(Scene* scene) override;
	void handleEvnets();

	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;
	bool bGameEnd = false;
};
