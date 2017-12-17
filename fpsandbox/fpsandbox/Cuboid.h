#pragma once
class Cuboid
{
	float posx, posy, posz;
	float sizex, sizey, sizez;
	float vertices[24]{};
	void generate();
	int indicies[36] = 
	{
		
	};
public:
	Cuboid();
	Cuboid(float, float, float, float, float,float);
	~Cuboid();

	void setSize(float, float, float);
	float getSizeX() { return sizex; };
	float getSizeY() { return sizey; };
	float getSizeZ() { return sizez; };

	void setPos(float, float, float);
	float getPosX() { return posx; };
	float getPosY() { return posy; };
	float getPosZ() { return posz; };
};

