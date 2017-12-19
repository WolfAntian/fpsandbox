#include "Camera.h"



void Camera::init(float posx, float posy, float posz, float yaw, float pitch)
{
	this->posx = posx;
	this->posy = posy; 
	this->posz = posz;
	this->yaw = yaw;
	this->setPitch(pitch);
}

Camera::Camera()
{
	init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Camera::Camera(float posx, float posy, float posz, float yaw, float pitch)
{
	init(posx, posy, posz, yaw, pitch);
}


Camera::~Camera()
{
}

void Camera::setPitch(float pitch)
{

	this->pitch = pitch;
	if (this->pitch > 80.0f) {
		this->pitch = 80.0f;
	}
	else if (pitch < -80.0f) {
		this->pitch = -80.0f;
	}

}
void Camera::addPitch(float pitch) 
{ 
	setPitch(getPitch() + pitch); 
}

glm::mat4 Camera::generateInverseMatrix()
{
	glm::mat4 view;
	
	view = glm::rotate(view, glm::radians(-pitch), glm::vec3(1.0, 0.0, 0.0));
	view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0, 1.0, 0.0));
	view = glm::translate(view, glm::vec3(posx, posy, posz));
	
	
	return view;
}
