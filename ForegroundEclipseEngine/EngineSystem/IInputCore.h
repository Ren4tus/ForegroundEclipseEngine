#pragma once
class Vector3D;
class IInputCore
{
public:
	virtual void Update() = 0;
	virtual void Clean() = 0;
	virtual bool getMouseButtonState(int buttonNumber) const = 0;
	virtual Vector3D* getMousePosition() const = 0;
};
