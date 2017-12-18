#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class GLLoader
{
public:
	GLLoader();
	~GLLoader();

	unsigned int loadVAO();
	unsigned int loadVertexBuffer(float vertices[], int verticesLength, unsigned int vao);
	unsigned int loadIndexBuffer(unsigned int indices[], int indicesLength, unsigned int vao);
	void loadUniformVariableMat4(std::string location, glm::mat4 value, unsigned int shader);

	void deleteVAO(unsigned int vao) { glDeleteVertexArrays(1, &vao); };
	void deleteVBO(unsigned int vbo) { glDeleteBuffers(1, &vbo); };
};

