#include "GLLoader.h"

#include <glad/glad.h>
#include <iostream>

GLLoader::GLLoader()
{
}


GLLoader::~GLLoader()
{	
}

unsigned int GLLoader::loadVAO()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}

unsigned int GLLoader::loadVertexBuffer(float vertices[], int verticesLength, unsigned int vao)
{
	unsigned int verticesBufferObject;
	glGenBuffers(1, &verticesBufferObject);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferObject);
	glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //vertices
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //normals
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return verticesBufferObject;
}

unsigned int GLLoader::loadIndexBuffer(unsigned int indices[], int indicesLength, unsigned int vao)
{
	unsigned int indicesBufferObject;
	glGenBuffers(1, &indicesBufferObject);

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return indicesBufferObject;
}

void GLLoader::loadUniformVariableMat4(std::string location, glm::mat4 value, unsigned int shader)
{
	unsigned int loc = glGetUniformLocation(shader, location.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void GLLoader::loadUniformVariableVec3(std::string location, float x, float y, float z, unsigned int shader)
{
	unsigned int loc = glGetUniformLocation(shader, location.c_str());
	glUniform3f(loc, x,y,z);
}
