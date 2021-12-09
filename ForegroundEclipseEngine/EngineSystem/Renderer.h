#pragma once
#include <string>
#include "../GameElements/Component.h"
class EngineSystem;
class Renderer : public Component
{
public:
	Renderer()
	{
	}

	~Renderer()
	{
	}

private:
	void Init(std::string SDK_Name) const;
public:
	
	EngineSystem* currentEngine;
};
