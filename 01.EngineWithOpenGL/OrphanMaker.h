#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "../ForegroundEclipseEngine/EngineSystem/glSystem/Shaders/shaderClass.h"
#include "../ForegroundEclipseEngine/GameElements/Monobehavior.h"
#include "../ForegroundEclipseEngine/GameElements/GameObject.h"
class OrphanMaker : public Monobehavior
{
public:
	GameObject* child;
	GameObject* parent;
	OrphanMaker(GameObject* child, GameObject* parent) 
	{
		this->child = child;
		this->parent = parent;
	}
	inline void ParentRemoveTest(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			parent->RemoveChild(child);
			std::cout << "parent deleted" << std::endl;
		}
	}
	inline virtual void Update() override {
		ParentRemoveTest(dynamic_cast<glSystem*>(GM::Instance()->GetCurrentEngine())->GetWindow());
	}
};