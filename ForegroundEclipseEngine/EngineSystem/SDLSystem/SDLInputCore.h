#pragma once
#include <vector>
#include <map>
#include "../IInputCore.h"
class SDLInputCore : public IInputCore
{
public:
	SDLInputCore() {}
	virtual ~SDLInputCore();
public:
	virtual void Update();
	virtual void Clean();
	virtual bool isKeyDown(SDL_Scancode key);
	virtual bool isKeyOneDown(SDL_Scancode key);
	virtual bool getMouseButtonState(int buttonNumber) const;
	virtual Vector3D* getMousePosition() const;
private:
	const Uint8* m_keystates;
	std::vector<bool> m_mouseButtonStates;
	Vector3D* m_mousePosition;
	std::map<int, bool> pressedMap;
};
enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};