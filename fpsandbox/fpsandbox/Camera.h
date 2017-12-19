#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//acts as a view port for the user to see the world from
//can be controlled in an fps style camera using mouse and wasd
class Camera
{
	float posx, posy, posz, //position
		yaw, //y rot
		pitch; //x rot, needs to be limited to +-80deg

	//initializes the class as there are multiple constructors
	void init(float posx, float posy, float posz, float yaw, float pitch);
public:
	Camera();
	Camera(float posx, float posy, float posz, float yaw, float pitch);
	~Camera();

	//setters
	void setPosX(float x) { this->posx = x; };
	void setPosY(float y) { this->posy = y; };
	void setPosZ(float z) { this->posz = z; };
	void setYaw(float yaw) { this->yaw = yaw; };
	void setPitch(float pitch);

	//setters (mutates current value)
	void addPosX(float x) { this->posx += x; };
	void addPosY(float y) { this->posy += y; };
	void addPosZ(float z) { this->posz += z; };
	void addYaw(float yaw) { this->yaw += yaw; };
	void addPitch(float pitch);

	//getters
	float getPosX() { return posx; };
	float getPosY() { return posy; };
	float getPosZ() { return posz; };
	float getYaw() { return yaw; };
	float getPitch() { return pitch; };

	//generates the view matrix 
	glm::mat4 generateInverseMatrix();
};

