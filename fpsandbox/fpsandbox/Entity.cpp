#include "Entity.h"

void Entity::setTransformation(float posx, float posy, float posz, float rotx, float roty, float rotz, float scale)
{
	pos = glm::vec3(posx, posy, posz);
	rot = glm::vec3(rotx, roty, rotz);
	this->scale = scale;
}

void Entity::setPos(float x, float y, float z)
{
	pos = glm::vec3(x, y, z);
}

void Entity::addPos(float x, float y, float z)
{
	pos += glm::vec3(x, y, z);
}

void Entity::setRot(float x, float y, float z)
{
	rot = glm::vec3(x, y, z);
}

void Entity::addRot(float x, float y, float z)
{
	rot = glm::vec3(x, y, z);
}

void Entity::setScale(float value)
{
	scale = value;
}

glm::mat4 Entity::getMatrix()
{
	glm::mat4 trans;
	trans = glm::translate(trans, pos);
	trans = glm::rotate(trans, glm::radians(rot[0]), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rot[1]), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rot[2]), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(scale, scale, scale));

	return trans;
}

Entity::Entity(RawModel * rawModel)
{
	this->rawModel = rawModel;
	scale = 1.0f;
}

Entity::~Entity()
{
}
