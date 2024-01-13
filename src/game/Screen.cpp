#include "GraphicObject.h"
#include "Screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>


Menu::Menu(GLFWwindow* _window, std::string background_texture,int _width, int _height):
	window(_window), 
	width(_width), 
	height(_height)
	{
	// programID = -1;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	background = GraphicObject();
	std::vector< glm::vec3 > vertices = std::vector< glm::vec3 >();
	vertices.push_back({ -1.0f, -1.0f, 0.0f });
	vertices.push_back({ 1.0f, -1.0f, 0.0f });
	vertices.push_back({ 1.0f, 1.0f, 0.0f});
	vertices.push_back({ -1.0f, -1.0f, 0.0f });
	vertices.push_back({ 1.0f, 1.0f , 0.0f});
	vertices.push_back({ -1.0f, 1.0f , 0.0f});
	std::vector< glm::vec2 > uvbufferdata;
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ 1.0f, 0.0f });
	uvbufferdata.push_back({ 1.0f, 1.0f });
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ 1.0f,1.0f });
	uvbufferdata.push_back({ 0.0f, 1.0f });
	background.setVertices(vertices);
	background.setTexture(uvbufferdata, background_texture);
	addGraphicObject(background);

	programID = LoadShaders("../src/assets/shaders/DefaultVertex.glsl", "../src/assets/shaders/DefaultFragment.glsl");

}

Menu::~Menu(){}

void Menu::updateAnimationLoop(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use our shader
	glUseProgram(programID);
    // background.draw();
    for(auto obj:objects){
		
        obj.draw();
    }

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Menu::addGraphicObject(GraphicObject& object){
	objects.push_back(object);
}

void Menu::cleanup(){
	// background.cleanup();
	for(auto obj:objects){
		obj.cleanup();
	}
	glDeleteProgram(programID);
}
void Menu::computeMatricesFromInputs(){}

Game::Game(GLFWwindow* _window, int _width, int _height):
	window(_window),
	width(_width),
	height(_height)
	{
	initialPosition = glm::vec3( 0, 0, 5 );
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
    mouseSensetivity = 0.3f;
    speed = 1.0f;
    mouseSpeed = 0.005f;
	visibilityRadius = 20.0f;

	programID = LoadShaders("../src/assets/shaders/VertexShader.glsl", "../src/assets/shaders/FragmentShader.glsl");
    projectionMatrixID = glGetUniformLocation(programID, "P");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	modelMatrixID = glGetUniformLocation(programID, "M");
	visibilityRadiusID = glGetUniformLocation(programID, "visibilityRadius");
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
Game::~Game(){}
glm::mat4 Game::getViewMatrix(){return ViewMatrix;}
glm::mat4 Game::getProjectionMatrix(){return ProjectionMatrix;}

void Game::updateAnimationLoop(){
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
    for(auto obj:objects){
        //glm::mat4 MVP = ProjectionMatrix * ViewMatrix * obj.M;

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &obj.M[0][0]);
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniform1f(visibilityRadiusID, visibilityRadius);

        obj.draw();
    }
	// glm::mat4 MVP = ProjectionMatrix * ViewMatrix * object->M;

	// // Send our transformation to the currently bound shader, 
	// // in the "MVP" uniform
	// glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	// glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &object->M[0][0]);
	// glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);


	// object->draw();
	

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

}

void Game::computeMatricesFromInputs(){
    
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse initialPosition
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse initialPosition for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSensetivity * mouseSpeed * float(1024/2 - xpos );
	if((verticalAngle + mouseSensetivity * mouseSpeed * float( 768/2 - ypos ) < 3.14f/4) && (verticalAngle + mouseSensetivity * mouseSpeed * float( 768/2 - ypos ) > -3.14f/4)){
		verticalAngle   += mouseSensetivity * mouseSpeed * float( 768/2 - ypos );
	}
    // std::cout << "angle: " << horizontalAngle << "\n";

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	glm::vec3 front = glm::vec3(sin(horizontalAngle), 0 , cos(horizontalAngle));
	// Up vector
	glm::vec3 up = glm::cross( right, direction );
    if (glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) != GLFW_PRESS){
        speed = 1.0f;
	}
    if (glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
        speed = 2.5f;
	}
	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		initialPosition += front * deltaTime * speed;

	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		initialPosition -= front * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		initialPosition += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		initialPosition -= right * deltaTime * speed;
	}
    
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								initialPosition,           // Camera is here
								initialPosition+direction, // and looks here : at the same initialPosition, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void Game::addGraphicObject(GraphicObject& object){
	objects.push_back(object);
}

void Game::cleanup(){
	for(auto obj:objects){
		obj.cleanup();
	}
	glDeleteProgram(programID);
}