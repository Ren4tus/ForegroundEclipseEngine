#include "SDLInputHandler.h"
#include <iostream>
#include "../GameManager.h"
#include "../SystemBase/SDLSystem.h"
SDLInputHandler* SDLInputHandler::s_pInstance = 0;
SDLInputHandler::SDLInputHandler() {
	m_keystates = NULL;

	m_mousePosition = glm::vec2(0, 0);

	for (int i = 0; i < 3; i++) {
		m_mouseButtonStates.push_back(false);
	}
}
void SDLInputHandler::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			dynamic_cast<SDLSystem*>(GM::Instance()->GetCurrentEngine())->clean();
		}
		else if (event.type == SDL_KEYUP) {
			m_keystates = SDL_GetKeyboardState(0);
		}
		else if (event.type == SDL_KEYDOWN) {
			m_keystates = SDL_GetKeyboardState(0);
		}

		if (event.type == SDL_MOUSEMOTION) {
			m_mousePosition.x = (float)event.motion.x;
			m_mousePosition.y = (float)event.motion.y;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				m_mouseButtonStates[LEFT] = true;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				m_mouseButtonStates[MIDDLE] = true;
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				m_mouseButtonStates[RIGHT] = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				m_mouseButtonStates[LEFT] = false;
			}
			if (event.button.button == SDL_BUTTON_MIDDLE) {
				m_mouseButtonStates[MIDDLE] = false;
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				m_mouseButtonStates[RIGHT] = false;
			}
		}
	}
}
void SDLInputHandler::clean()
{
	m_keystates = NULL;
}
bool SDLInputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0) {
		if (m_keystates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool SDLInputHandler::isKeyOneDown(SDL_Scancode key)
{
	if (m_keystates != 0) {
		if (m_keystates[key] == 1) {
			if (pressedMap[key] == false) {
				pressedMap[key] = true;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			pressedMap[key] = false;
			return false;
		}
	}
	return false;
}
bool SDLInputHandler::getMouseButtonState(int buttonNumber) const {
	return m_mouseButtonStates[buttonNumber];
}
glm::vec2 SDLInputHandler::getMousePosition() const {
	return m_mousePosition;
}