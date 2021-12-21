#pragma once
#include "SDL.h"
#include <vector>
#include <map>
#include <string>
#include "../../pch.h"
class SDLInputHandler
{
public:
	~SDLInputHandler() {}
	static SDLInputHandler* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new SDLInputHandler();
		}
		return s_pInstance;
	}

	void update();
	void clean();
	bool isKeyDown(SDL_Scancode key);
	bool isKeyOneDown(SDL_Scancode key);
	bool getMouseButtonState(int buttonNumber) const;
	glm::vec2 getMousePosition() const;
private:
	SDLInputHandler();

	static SDLInputHandler* s_pInstance;
	const Uint8* m_keystates;
	std::vector<bool> m_mouseButtonStates;
	glm::vec2 m_mousePosition;
	std::map<int, bool> pressedMap;
};

typedef SDLInputHandler TheInputHandler;
enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};