#pragma once

#include <glad/glad.h>
class Shader
{
	
	void createShader(GLuint type);
	void createShaderProgram();
public:
	Shader();
	~Shader();

	unsigned int id, vertexId, fragmentId;

	unsigned int getId() { return id; };
	unsigned int getVertexId() { return vertexId; };
	unsigned int getFragmentId() { return fragmentId; };

};

