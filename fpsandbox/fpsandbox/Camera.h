#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	float posx, posy, posz,
		yaw, //y
		pitch; //x needs to be limited to +-80deg

	void init(float posx, float posy, float posz, float yaw, float pitch);
public:
	Camera();
	Camera(float posx, float posy, float posz, float yaw, float pitch);
	~Camera();

	void setPosX(float x) { this->posx = x; };
	void setPosY(float y) { this->posy = y; };
	void setPosZ(float z) { this->posz = z; };
	void setYaw(float yaw) { this->yaw = yaw; };
	void setPitch(float pitch);

	void addPosX(float x) { this->posx += x; };
	void addPosY(float y) { this->posy += y; };
	void addPosZ(float z) { this->posz += z; };
	void addYaw(float yaw) { this->yaw += yaw; };
	void addPitch(float pitch);

	float getPosX() { return posx; };
	float getPosY() { return posy; };
	float getPosZ() { return posz; };
	float getYaw() { return yaw; };
	float getPitch() { return pitch; };

	glm::mat4 generateInverseMatrix();
};

