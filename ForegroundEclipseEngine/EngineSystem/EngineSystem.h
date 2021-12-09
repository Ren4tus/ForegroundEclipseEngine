#pragma once
#include <string>
#include <memory>
class IEngineRendererCore;
class IInputCore;
class EngineSystem
{
public:
	EngineSystem(){}
	

	~EngineSystem()
	{
	}

public:
	virtual bool BuildSystem() = 0;
	virtual bool SystemInit() = 0;
	std::string EngineType;
protected:
	//typedef std::shared_ptr<Renderer> RendererPtr;
	IEngineRendererCore* renderCore;
	IInputCore* inputCore;
private:
};
