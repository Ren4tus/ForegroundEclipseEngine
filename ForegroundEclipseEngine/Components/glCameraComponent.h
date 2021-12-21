#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "../EngineSystem/glSystem/Shaders/shaderClass.h"
#include "../GameElements/Behaviour.h"
class glCameraComponent : public Behaviour
{
public:
	glCameraComponent(int width, int height, glm::vec3 position);

	inline void SetDefaultInput(bool val) { defaultInputUse = val; }
	inline void SetWindow(GLFWwindow* window) { this->window = window; }

	// ī�޶��� ����� vertext shader�� ������Ʈ
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// ī�޶� ����� ���̴��� ������
	void Matrix(Shader& shader, const char* uniform);
	void Inputs();

	// ī�޶��� ��ġ ����
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// �⺻ ī�޶� ������ ��� ����
	bool defaultInputUse = true;

	// ���콺 ���� ��ư�� ó�� Ŭ���� �� ī�޶� Ƣ�� �� ����.
	bool firstClick = true;

	// �������� width, height
	int width;
	int height;

	// ī�޶� �����̴� �ӵ��� �ΰ���
	float speed = 0.01f;
	float sensitivity = 100.0f;

private:
	GLFWwindow* window;
};