#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>



void Shader::createShader(GLuint type)
{
	std::string file, err;
	unsigned int* id;
	
	switch (type) {
	case GL_VERTEX_SHADER:
		file = ("VertexShader.glsl");
		err = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
		id = &vertexId;
		break;
	case GL_FRAGMENT_SHADER:
		file = ("FragmentShader.glsl");
		err = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
		id = &fragmentId;
		break;
	};

	std::string src = "";
	std::ifstream input(file);
	if (input.is_open())
		src.append((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
	const char *srcc = src.c_str();
	input.close();
	*id = glCreateShader(type);
	glShaderSource(*id, 1, &srcc, NULL);
	glCompileShader(*id);
	//validate
	int  success;
	char infoLog[512];
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		std::cout << err << infoLog << std::endl;
	}
}

void Shader::createShaderProgram()
{
}

Shader::Shader()
{


}


Shader::~Shader()
{
}
