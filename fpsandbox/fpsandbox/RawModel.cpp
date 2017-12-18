#include "RawModel.h"
#include "RawModel.h"


void RawModel::init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader) 
{
	vao = loader->loadVAO();
	vertexBuffer = loader->loadVertexBuffer(vertices, verticesLength, vao);
	indexBuffer = loader->loadIndexBuffer(indices, indicesLength, vao);
	this->loader = loader;
}


RawModel::RawModel(GLLoader * loader)
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	init(vertices, 12, indices, 6, loader);
}

RawModel::RawModel(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader)
{
	init(vertices, verticesLength, indices, indicesLength, loader);
}


RawModel::~RawModel()
{
	loader->deleteVAO(vao);
	loader->deleteVBO(vertexBuffer);
	loader->deleteVBO(indexBuffer);
}
