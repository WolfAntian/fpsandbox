#pragma once

#include <glad/glad.h>

#include "GLLoader.h"

class RawModel
{
	unsigned int vao, vertexBuffer, indexBuffer, indexBufferSize;
	GLLoader* loader;

	void init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);
public:
	RawModel(GLLoader* loader);
	RawModel(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);
	~RawModel();

	unsigned int getVAO() { return vao; };
	unsigned int getIndexBufferSize() { return indexBufferSize; };
};

