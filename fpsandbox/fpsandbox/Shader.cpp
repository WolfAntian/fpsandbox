#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>



void Shader::createShader(GLuint type)
{
	std::string file, err;
	unsigned int* id = 0;
	
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
	id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);
	glLinkProgram(id);
	int  success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

Shader::Shader()
{
	createShader(GL_VERTEX_SHADER);
	createShader(GL_FRAGMENT_SHADER);
	createShaderProgram();
	glUseProgram(id);
}


Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(id);
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}
