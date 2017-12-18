#include "GLLoader.h"

#include <glad/glad.h>
#include <iostream>

GLLoader::GLLoader()
{
}


GLLoader::~GLLoader()
{
	
	/*for (auto const& vao : vaos) {
		glDeleteVertexArrays(1, &vao );
	}
	for (auto const& vbo : vbos) {
		glDeleteVertexArrays(1, &vbo);
	}*/

	
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	unsigned int transformLoc = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
