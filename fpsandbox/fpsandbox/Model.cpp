#include "Model.h"

#include <iostream>

RawModel::RawModel(GLLoader* loader)
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
	init(vertices, 12, indices, 6, loader);
}


RawModel::~RawModel()
{
	loader->deleteVAO(vao);
	loader->deleteVBO(vertexBufferObject);
	loader->deleteVBO(indexBufferObject);
}

void RawModel::init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader * loader)
{
	std::cout << vertices[0] << vertices[1] << vertices[2] << vertices[3] << vertices[4] << vertices[5] << std::endl;
	std::cout << indices[0] << indices[1] << indices[2] << indices[3] << indices[4] << indices[5] << std::endl;
	this->vao = loader->loadVAO();
	this->vertexBufferObject = loader->loadVertices(vertices, verticesLength, vao);
	this->indexBufferObject = loader->loadIndices(indices, indicesLength, vao);
	this->loader = loader;
}

//##########################################################################
//############################## # Model # ################################
//##########################################################################

void Model::setTransformation(float posx, float posy, float posz, float rotx, float roty, float rotz, float scale)
{
	pos = glm::vec3(posx, posy, posz);
	rot = glm::vec3(rotx, roty, rotz);
	this->scale = scale;
}

void Model::setPos(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

void Model::addPos(float x, float y, float z)
{
	pos += glm::vec3(x, y, z);
}

void Model::setRot(float x, float y, float z)
{
	rot = glm::vec3(x, y, z);
}

void Model::addRot(float x, float y, float z)
{
	rot = glm::vec3(x, y, z);
}

glm::mat4 Model::getMatrix()
{
	glm::mat4 trans;
	trans = glm::translate(trans, pos);
	trans = glm::rotate(trans, glm::radians(rot[0]), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rot[1]), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rot[2]), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(scale, scale, scale));

	return trans;
}


Model::Model(RawModel * rawModel)
{
	this->rawModel = rawModel;
}

Model::~Model()
{
}
