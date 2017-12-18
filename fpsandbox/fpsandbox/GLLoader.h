#pragma once

#include <vector>

class GLLoader
{
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
public:
	GLLoader();
	~GLLoader();

	void loadToVAO(float vertices[], int verticesLength, unsigned int indices[], int indicesLength);
	std::vector<unsigned int> getVAOs() { return vaos; };
	

};

