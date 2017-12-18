#include "GLLoader.h"

#include <glad/glad.h>
#include <iostream>

GLLoader::GLLoader()
{
}


GLLoader::~GLLoader()
{
	
	for (auto const& vao : vaos) {
		glDeleteVertexArrays(1, &vao );
	}
	for (auto const& vbo : vbos) {
		glDeleteVertexArrays(1, &vbo);
	}

	
}

void GLLoader::loadToVAO(float vertices[], int verticesLength, unsigned int indices[], int indicesLength)
{
	unsigned int VAO;
	unsigned int verticesBufferObject;
	unsigned int indicesBufferObject;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &verticesBufferObject);
	glGenBuffers(1, &indicesBufferObject);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferObject);
	glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
	vaos.push_back(VAO);
	vbos.push_back(verticesBufferObject);
	vbos.push_back(indicesBufferObject);
}
