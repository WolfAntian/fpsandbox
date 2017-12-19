#include "RawModel.h"
#include "RawModel.h"


void RawModel::init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader) 
{
	vao = loader->loadVAO();
	vertexBuffer = loader->loadVertexBuffer(vertices, verticesLength, vao);
	indexBuffer = loader->loadIndexBuffer(indices, indicesLength, vao);
	this->indexBufferSize = indicesLength;
	this->loader = loader;
}


RawModel::RawModel(GLLoader * loader)
{
	//defaults to cube
	float vertices[24] =
	{
		-1, -1, -1,
		1, -1, -1,
		1, 1, -1,
		-1, 1, -1,
		-1, -1, 1,
		1, -1, 1,
		1, 1, 1,
		-1, 1, 1
	};
	unsigned int indices[36] =
	{
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};
	init(vertices, 24, indices, 36, loader);
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
