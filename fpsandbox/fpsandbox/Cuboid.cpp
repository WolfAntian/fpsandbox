#include "Cuboid.h"

Cuboid::Cuboid()
{
	Cuboid(0, 0, 0, 0, 0, 0);
}

Cuboid::Cuboid(float posx, float posy, float posz, float sizex, float sizey, float sizez)
{
	this->posx = posx;
	this->posy = posy;
	this->posz = posz;
	this->sizex = sizex;
	this->sizey = sizey;
	this->sizez = sizez;
	generate();
}

Cuboid::~Cuboid()
{
}

void Cuboid::setSize(float sizex, float sizey, float sizez)
{
	this->sizex = sizex;
	this->sizey = sizey;
	this->sizez = sizez;
	generate();
}

void Cuboid::setPos(float posx, float posy, float posz)
{
	this->posx = posx;
	this->posy = posy;
	this->posz = posz;
	generate();
}

void Cuboid::generate()
{
	//front top left	0
	this->vertices[0] = -sizex / 2 + posx;
	this->vertices[1] = sizey / 2 + posy;
	this->vertices[2] = -sizez / 2 + posz;
	//front bottom left	1
	this->vertices[3] = -sizex / 2 + posx;
	this->vertices[4] = -sizey / 2 + posy;
	this->vertices[5] = -sizez / 2 + posz;
	//front botom right	2
	this->vertices[6] = sizex / 2 + posx;
	this->vertices[7] = -sizey / 2 + posy;
	this->vertices[8] = -sizez / 2 + posz;
	//front top right	3
	this->vertices[9] = sizex / 2 + posx;
	this->vertices[10] = sizey / 2 + posy;
	this->vertices[11] = -sizez / 2 + posz;
	//back top left		4
	this->vertices[12] = -sizex / 2 + posx;
	this->vertices[13] = sizey / 2 + posy;
	this->vertices[14] = sizez / 2 + posz;
	//back bottom left	5
	this->vertices[15] = -sizex / 2 + posx;
	this->vertices[16] = -sizey / 2 + posy;
	this->vertices[17] = sizez / 2 + posz;
	//back botom right	6
	this->vertices[18] = sizex / 2 + posx;
	this->vertices[19] = -sizey / 2 + posy;
	this->vertices[20] = sizez / 2 + posz;
	//back top right	7
	this->vertices[21] = sizex / 2 + posx;
	this->vertices[22] = sizey / 2 + posy;
	this->vertices[23] = sizez / 2 + posz;

}