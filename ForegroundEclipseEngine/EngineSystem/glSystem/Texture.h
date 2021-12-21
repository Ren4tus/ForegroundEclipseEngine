#pragma once

#include<glad/glad.h>
#include"../../Utilities/stb_image.h"

#include"Shaders/shaderClass.h"

class Texture
{
public:
	Texture(const char* image, const char* texType, GLuint slot);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
	const char* type;
	GLuint unit;
};