#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RawModel.h"

//an entity within the world
//records the positioning and scale of an entity within the world
//also holds the RawModel it uses, these are kept seperate for batch rendering
class Entity
{
	RawModel* rawModel; //the model which the enitity looks like

	glm::vec3 pos; //position
	glm::vec3 rot; //rotation
	glm::vec3 scale; //scale/size
	glm::vec3 colour; //colour

public:
	Entity(RawModel* rawModel);
	~Entity();

	//setters
	void setTransformation(float posx, float posy, float posz, float rotx, float roty, float rotz, float scale);
	void setPos(float x, float y, float z);
	void setRot(float x, float y, float z);
	void setScale(float value);
	void setScale(float x, float y, float z);
	void setColour(float r, float g, float b);
	//setters (mutates current value)
	void addRot(float x, float y, float z);
	void addPos(float x, float y, float z);

	//getters
	glm::vec3 getColour() { return colour; };
	glm::mat4 getMatrix(); //generates the matrix that describes position and rotation
	RawModel* getRawModel() { return rawModel; };
};

