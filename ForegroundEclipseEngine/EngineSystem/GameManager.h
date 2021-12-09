#pragma once
#include <string>
#include <fstream>
//#include <SDL.h>
class EngineSystem;
class GameManager {
public:



	//bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	//void render();
	//void update();
	//bool running() { return m_bRunning; }
	//void handleEvents();
	//void clean();
	
	//SDL_Renderer* getRenderer() const { return m_pRenderer; }

	//void quit() {
	//	m_bRunning = false;
	//}
	//void setWindowScreen(int width, int height);
	//int getWindowWidth();
	//int getWindowHeight();
private:
	std::string ProjectFolderPath;
public:
	EngineSystem* LoadEngineSystemByConfig();
	
private:
	GameManager();
	static GameManager* s_pInstance;
	EngineSystem* QueryEngineType(std::string EngineType);

	//SDL_Window* m_pWindow;
	//SDL_Renderer* m_pRenderer;
	//bool m_bRunning;
	//int m_currentFrame;
	//std::vector<GameObject*> m_gameObjects;
	//int SCREEN_WIDTH;
	//int SCREEN_HEIGHT;
	//GameStateMachine* m_pGameStateMachine;
public:
	~GameManager();
	static GameManager* Instance();
};
typedef GameManager GM;