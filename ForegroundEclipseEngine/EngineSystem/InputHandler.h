#pragma once
#include <vector>
#include <map>
#include <string>
class InputHandler
{
public:
	~InputHandler() {}
	static InputHandler* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
private:
	InputHandler();
	static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;