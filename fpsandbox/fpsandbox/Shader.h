#pragma once

#include <glad/glad.h>

//interface for the shader program
class Shader
{
	unsigned int id, vertexId, fragmentId; //ids

	//creates each type of shader, vertex+frament
	void createShader(GLuint type);
	//binds together shaders
	void createShaderProgram();
public:
	Shader();
	~Shader();

	//getters
	unsigned int getId() { return id; };
	unsigned int getVertexId() { return vertexId; };
	unsigned int getFragmentId() { return fragmentId; };

};

