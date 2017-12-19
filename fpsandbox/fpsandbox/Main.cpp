#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _CRTDBG_MAP_ALLOC  
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <stdlib.h>  
#include <crtdbg.h>  

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "Shader.h"
#include "GLLoader.h"
#include "RawModel.h"
#include "Entity.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void init();
void logic();
void render();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Shader* shader;
GLLoader* loader;
RawModel* model;
Entity* entity;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FPSandbox", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	init();

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		logic();
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;
	delete loader;
	delete model;
	delete entity;
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	_CrtDumpMemoryLeaks();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void init() {

	shader = new Shader();

	loader = new GLLoader();

	model = new RawModel(loader);

	entity = new Entity(model);

	entity->setPos(0.0f, 0.0f, 0.0f);
	entity->setRot(25.0f, 0.0f, 0.0f);
	entity->setScale(1.0f);
	loader->loadUniformVariableMat4("model", entity->getMatrix(), shader->getId());

	glm::mat4 view;
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(75.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 1.f, 32768.f);

	loader->loadUniformVariableMat4("view", view, shader->getId());
	loader->loadUniformVariableMat4("projection", projection, shader->getId());

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void logic() {

}

void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*std::vector<unsigned int> vaos = loader->getVAOs();
	for (auto const& vao : vaos) {
		std::cout << vao << std::endl;
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}*/

	glBindVertexArray(entity->getRawModel()->getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}