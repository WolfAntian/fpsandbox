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
#include <vector>

#include "Shader.h"
#include "GLLoader.h"
#include "RawModel.h"
#include "Entity.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void init(GLFWwindow* window);
void logic(GLFWwindow* window);
void render();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Shader* shader;
GLLoader* loader;
RawModel* model;
Camera* camera;
std::vector<Entity*>* entities;

float deltaTime = 0.0f;
float lastTime = 0.0f;
float lastMouseX = 400, lastMouseY = 300;

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

	init(window);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		
		logic(window);
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete shader;
	delete loader;
	delete model;
	delete camera;
	for (auto const& entity : *entities) {
		delete entity;
	}
	delete entities;
	
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
	//keyboard
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float moveSpeed = deltaTime * 6.0f; // adjust accordingly	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->addPosZ(cos(glm::radians(camera->getYaw())) * moveSpeed);
		camera->addPosX(-sin(glm::radians(camera->getYaw())) * moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->addPosZ(-cos(glm::radians(camera->getYaw())) * moveSpeed);
		camera->addPosX(sin(glm::radians(camera->getYaw())) * moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->addPosX(cos(glm::radians(camera->getYaw())) * moveSpeed);
		camera->addPosZ(sin(glm::radians(camera->getYaw())) * moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->addPosX(-cos(glm::radians(camera->getYaw())) * moveSpeed);
		camera->addPosZ(-sin(glm::radians(camera->getYaw())) * moveSpeed);
	}



	//mouse
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos; 
	lastMouseX = xpos;
	lastMouseY = ypos;

	float mouseSensitivity = 0.05f;
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	camera->addYaw(xoffset);
	camera->addPitch(yoffset);

	std::cout << camera->getYaw() << "::" << camera->getPitch() << std::endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


void init(GLFWwindow* window) {

	shader = new Shader();

	loader = new GLLoader();

	model = new RawModel(loader);

	camera = new Camera();

	entities = new std::vector<Entity*>;

	Entity* entity = new Entity(model);
	entity->setPos(0.0f, 0.0f, -10.0f);
	entity->setRot(45.0f, 0.0f, 0.0f);
	entities->push_back(entity);

	entity = new Entity(model);
	entity->setPos(1.0f, 1.0f, -2.0f);
	entity->setRot(12.0f, 270.0f, 98.0f);
	entities->push_back(entity);


	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 32768.f);
	loader->loadUniformVariableMat4("projection", projection, shader->getId());

	float currentTime = glfwGetTime();
	deltaTime = currentTime;
	lastTime = currentTime;
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}

void logic(GLFWwindow* window) {
	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	processInput(window);

	//camera->addPosZ(deltaTime * -3);

	loader->loadUniformVariableMat4("view", camera->generateInverseMatrix(), shader->getId());
}

void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(model->getVAO()); //all entities are using same model, do something similar for batch rendering 
	for (auto const& entity : *entities) {
		loader->loadUniformVariableMat4("model", entity->getMatrix(), shader->getId());
		glDrawElements(GL_TRIANGLES, model->getIndexBufferSize(), GL_UNSIGNED_INT, 0);
		
	}
	glBindVertexArray(0);

	/*glBindVertexArray(entity->getRawModel()->getVAO());
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/
}