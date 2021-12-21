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

	// 카메라의 행렬을 vertext shader로 업데이트
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// 카메라 행렬을 셰이더로 내보냄
	void Matrix(Shader& shader, const char* uniform);
	void Inputs();

	// 카메라의 위치 정보
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// 기본 카메라 움직임 사용 여부
	bool defaultInputUse = true;

	// 마우스 왼쪽 버튼을 처음 클릭할 때 카메라가 튀는 것 방지.
	bool firstClick = true;

	// 윈도우의 width, height
	int width;
	int height;

	// 카메라가 움직이는 속도와 민감도
	float speed = 0.01f;
	float sensitivity = 100.0f;

private:
	GLFWwindow* window;
};