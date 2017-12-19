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
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       

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
void loadCubes();

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//initialises the program, 
//anything needed to be set up at the start is done here except glfw stuff
void init(GLFWwindow* window) {

	shader = new Shader();

	loader = new GLLoader();

	model = new RawModel(loader);

	camera = new Camera();
	camera->addPosY(-1.0f);

	entities = new std::vector<Entity*>;

	loadCubes();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 32768.f);
	loader->loadUniformVariableMat4("projection", projection, shader->getId());

	float currentTime = glfwGetTime();
	deltaTime = currentTime;
	lastTime = currentTime;
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

//the logic done every frame
//updates objects that need to be updated etc
void logic(GLFWwindow* window) {
	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	processInput(window);

	
}

//renders the screen every frame
//makes things appear on screen
void render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	loader->loadUniformVariableMat4("view", camera->generateInverseMatrix(), shader->getId());
	loader->loadUniformVariableVec3("lightPos", -camera->getPosX(), -camera->getPosY(), -camera->getPosZ(), shader->getId());

	glBindVertexArray(model->getVAO()); //all entities are using same model, do something similar for batch rendering 
	for (auto const& entity : *entities) {
		loader->loadUniformVariableVec3("objColor", entity->getColour()[0], entity->getColour()[1], entity->getColour()[2], shader->getId());
		loader->loadUniformVariableMat4("model", entity->getMatrix(), shader->getId());
		glDrawElements(GL_TRIANGLES, model->getIndexBufferSize(), GL_UNSIGNED_INT, 0);
		
	}
	glBindVertexArray(0);

	/*glBindVertexArray(entity->getRawModel()->getVAO());
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/
}

//loads up some cubes 
void loadCubes() {

	srand(time(NULL));

	Entity* entity = new Entity(model);

	entity->setPos(0.0f, 0.0f, -10.0f);
	entity->setColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);
	entities->push_back(entity);

	entity = new Entity(model);
	entity->setPos(1.0f, 1.0f, -2.0f);
	entity->setColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);
	entity->setRot(45, 45, 0);
	entities->push_back(entity);

	entity = new Entity(model); //floor
	entity->setPos(0.0f, -0.05f, -0.0f);
	entity->setScale(1000, 0.1, 1000);
	entity->setColour(0.4, 0.4, 0.4);
	entities->push_back(entity);

	entity = new Entity(model);
	entity->setPos(10.0f, 0, -0.0f);
	entity->setScale(1, 10, 1);
	entity->setColour((rand() % 1000)/1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);
	entities->push_back(entity);


	for (int a = 0; a < 100; a++) {
		entity = new Entity(model);
		entity->setPos(10 + a, 0.0f, 3.0f);
		entity->setScale(1, 1+(rand() % 20), 1);
		entity->setColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);
		entities->push_back(entity);

		entity = new Entity(model);
		entity->setPos(10+a, 0.0f, -3.0f);
		entity->setScale(1, 1+(rand() % 20), 1);
		entity->setColour((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f);
		entities->push_back(entity);
	}


}