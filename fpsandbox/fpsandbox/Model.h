#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLLoader.h"



class RawModel
{
	GLLoader* loader;

	unsigned int vao;
	unsigned int vertexBufferObject;
	unsigned int indexBufferObject;

	void init(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);

public:
	RawModel(GLLoader* loader);
	RawModel(float vertices[], int verticesLength, unsigned int indices[], int indicesLength, GLLoader* loader);
	~RawModel();

	unsigned int getVAO() { return vao; };

};

class Model
{
	RawModel* rawModel;

	glm::vec3 pos;
	glm::vec3 rot;
	float scale;
public:
	Model(RawModel* rawModel);
	~Model();

	void setTransformation(float posx, float posy, float posz, float rotx, float roty, float rotz, float scale);
	void setPos(float x, float y, float z);
	void addPos(float x, float y, float z);
	void setRot(float x, float y, float z);
	void addRot(float x, float y, float z);
	glm::mat4 getMatrix();
	RawModel* getRawModel() { return this->rawModel; };
};

