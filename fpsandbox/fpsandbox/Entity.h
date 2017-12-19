#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RawModel.h"

class Entity
{
	RawModel* rawModel;

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
	glm::vec3 colour;

public:
	Entity(RawModel* rawModel);
	~Entity();

	RawModel* getRawModel() { return rawModel; };

	void setTransformation(float posx, float posy, float posz, float rotx, float roty, float rotz, float scale);
	void setPos(float x, float y, float z);
	void addPos(float x, float y, float z);
	void setRot(float x, float y, float z);
	void addRot(float x, float y, float z);
	void setScale(float value);
	void setScale(float x, float y, float z);
	void setColour(float r, float g, float b);
	glm::vec3 getColour() { return colour; };
	glm::mat4 getMatrix();
};

