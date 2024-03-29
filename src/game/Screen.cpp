#include "GraphicObject.h"
#include "Screen.h"
#include "window.h"
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


Menu::Menu(GLFWwindow* _window, std::string background_texture):
	window(_window), 
	width(1024), 
	height(768),
	status(OPEN)
	{
	// programID = -1;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use our shader
	glUseProgram(programID);
	computeMatricesFromInputs();
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
	for(auto obj:objects){
		obj.cleanup();
	}
	glDeleteProgram(programID);
}
void Menu::computeMatricesFromInputs(){
	switch(status){
		case OPEN:
			if(glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS){
				std::cout << "Changing status from OPEN to PROCESSING\n";
        		status = PROCESSING;
			}
			break;
		case PROCESSING:
			if(glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS){
				std::cout << "Changing status from OPEN to PROCESSING\n";
				status = CLOSED;
			}
			break;
	}
	
}

Game::Game(GLFWwindow* _window):
	window(_window),
	width(1024),
	height(768),
	status(OPEN)
	{
	PlayerPosition = glm::vec3( 0, 0, 0 );
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
    mouseSensetivity = 0.3f;
    speed = 1.0f;
    mouseSpeed = 0.005f;
	torch = 0;
	time = 0;
	programID = LoadShaders("../src/assets/shaders/VertexShader.glsl", "../src/assets/shaders/FragmentShader.glsl");
    projectionMatrixID = glGetUniformLocation(programID, "P");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
	modelMatrixID = glGetUniformLocation(programID, "M");
	torchID = glGetUniformLocation(programID, "torch");
	timeID = glGetUniformLocation(programID, "mytime");
}
Game::~Game(){}
glm::mat4 Game::getViewMatrix(){return ViewMatrix;}
glm::mat4 Game::getProjectionMatrix(){return ProjectionMatrix;}

void Game::updateAnimationLoop(){
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
    for(auto obj:objects){

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &obj.M[0][0]);
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniform1i(torchID, torch);
		glUniform1f(timeID, time);

        obj.draw();
    }
	glfwSwapBuffers(window);
	glfwPollEvents();

}

void Game::computeMatricesFromInputs(){
    
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	time = currentTime;
	// Get mouse PlayerPosition
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse PlayerPosition for next frame
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
		PlayerPosition += front * deltaTime * speed;

	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		PlayerPosition -= front * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		PlayerPosition += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		PlayerPosition -= right * deltaTime * speed;
	}
    if (glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS){
		if(torch == 0){
			torch = 2;
		}
		if(torch == 1){
			torch = 3;
		}
	}else{
		if(torch == 2){
			torch = 1;
		}
		if(torch == 3){
			torch = 0;
		}
	}
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								PlayerPosition,           // Camera is here
								PlayerPosition+direction, // and looks here : at the same PlayerPosition, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	switch(status){
		case OPEN:
			if(glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS){
				std::cout << "Changing status from OPEN to PROCESSING\n";
        		status = PROCESSING;
			}
			break;
		case PROCESSING:
			if(glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS){
				std::cout << "Changing status from OPEN to PROCESSING\n";
				status = CLOSED;
			}
			break;
	}
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
