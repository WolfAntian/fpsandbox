#pragma once

#include <glad/glad.h>

#include "GLLoader.h"

//the model that is rendered
//defaults to cube
class RawModel
{
	//id and data about the model
	unsigned int vao, vertexBuffer, indexBuffer, indexBufferSize;
	//loader that loads data into graphics
	GLLoader* loader;

	//init due to multiple constructors
	void init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);
public:
	RawModel(GLLoader* loader);
	RawModel(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);
	~RawModel();

	//getters
	unsigned int getVAO() { return vao; };
	unsigned int getIndexBufferSize() { return indexBufferSize; };
};

