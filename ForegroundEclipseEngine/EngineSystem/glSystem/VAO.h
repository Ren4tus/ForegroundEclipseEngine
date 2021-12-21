#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
};
