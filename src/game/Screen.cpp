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

Screen::Screen(GLFWwindow* _window): window(_window){
    initialPosition = glm::vec3( 0, 0, 5 );
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
    mouseSensetivity = 0.3f;
    speed = 1.0f;
    mouseSpeed = 0.005f;
    // object = nullptr;
    programID = -1;
    viewMatrixID = -1;
    projectionMatrixID = -1;
    modelMatrixID = -1;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
Screen::~Screen(){}
glm::mat4 Screen::getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 Screen::getProjectionMatrix(){
	return ProjectionMatrix;
}
void Screen::loadShaders(){
    programID = LoadShaders("../src/assets/shaders/VertexShader.glsl", "../src/assets/shaders/FragmentShader.glsl");
    projectionMatrixID = glGetUniformLocation(programID, "P");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
}

// void Screen::setGraphicObject(GraphicObject* new_object){
//     object = new_object;
// }
void Screen::addGraphicObject(GraphicObject& object){
    objects.push_back(object);
}

void Screen::computeMatricesFromInputs(){
    
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

void Screen::updateAnimationLoop(){
	
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

bool Screen::cleanup()
{
  // Cleanup VBO

    for(auto obj:objects){
        obj.cleanup();
    }
  glDeleteProgram(programID);
  return true;
}

Menu_Screen::Menu_Screen(GLFWwindow* _window): window(_window){
    // object = nullptr;
    programID = -1;
    viewMatrixID = -1;
    // matrixID = -1;
    projectionMatrixID = -1;
    modelMatrixID = -1;
    FoV = 45.0f;
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix       = 	glm::lookAt(
								glm::vec3(0,0,3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						    );
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}
Menu_Screen::~Menu_Screen(){}
glm::mat4 Menu_Screen::getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 Menu_Screen::getProjectionMatrix(){
	return ProjectionMatrix;
}
void Menu_Screen::loadShaders(){
    programID = LoadShaders("../src/assets/shaders/VertexShader.glsl", "../src/assets/shaders/FragmentShader.glsl");
    projectionMatrixID = glGetUniformLocation(programID, "P");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
}

// void Screen::setGraphicObject(GraphicObject* new_object){
//     object = new_object;
// }
void Menu_Screen::addGraphicObject(GraphicObject& object){
    objects.push_back(object);
}

// void Menu_Screen::computeMatricesFromInputs(){
    
// 	// glfwGetTime is called only once, the first time this function is called
// 	static double lastTime = glfwGetTime();

// 	// Compute time difference between current and last frame
// 	double currentTime = glfwGetTime();
// 	float deltaTime = float(currentTime - lastTime);

// 	// Get mouse initialPosition
// 	double xpos, ypos;
// 	glfwGetCursorPos(window, &xpos, &ypos);

// 	// Reset mouse initialPosition for next frame
// 	glfwSetCursorPos(window, 1024/2, 768/2);

// 	// Compute new orientation
// 	horizontalAngle += mouseSensetivity * mouseSpeed * float(1024/2 - xpos );
// 	if((verticalAngle + mouseSensetivity * mouseSpeed * float( 768/2 - ypos ) < 3.14f/4) && (verticalAngle + mouseSensetivity * mouseSpeed * float( 768/2 - ypos ) > -3.14f/4)){
// 		verticalAngle   += mouseSensetivity * mouseSpeed * float( 768/2 - ypos );
// 	}
	

// 	// Direction : Spherical coordinates to Cartesian coordinates conversion
// 	glm::vec3 direction(
// 		cos(verticalAngle) * sin(horizontalAngle), 
// 		sin(verticalAngle),
// 		cos(verticalAngle) * cos(horizontalAngle)
// 	);
	
// 	// Right vector
// 	glm::vec3 right = glm::vec3(
// 		sin(horizontalAngle - 3.14f/2.0f), 
// 		0,
// 		cos(horizontalAngle - 3.14f/2.0f)
// 	);
	
// 	glm::vec3 front = glm::vec3(sin(horizontalAngle), 0 , cos(horizontalAngle));
// 	// Up vector
// 	glm::vec3 up = glm::cross( right, direction );

// 	// Move forward
// 	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
// 		initialPosition += front * deltaTime * speed;
// 	}
// 	// Move backward
// 	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
// 		initialPosition -= front * deltaTime * speed;
// 	}
// 	// Strafe right
// 	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
// 		initialPosition += right * deltaTime * speed;
// 	}
// 	// Strafe left
// 	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
// 		initialPosition -= right * deltaTime * speed;
// 	}
// 	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

// 	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	
// 	// Camera matrix
	

// 	// For the next frame, the "last time" will be "now"
// 	lastTime = currentTime;
// }

void Menu_Screen::updateAnimationLoop(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
    // glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 scaleMatrix =	glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)); 
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f),glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 Model = translationMatrix * rotationMatrix * scaleMatrix;

    for(auto obj:objects){
        // glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model;

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &Model[0][0]);
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);


        obj.draw();
    }

	glfwSwapBuffers(window);
	glfwPollEvents();

}

bool Menu_Screen::cleanup()
{
  // Cleanup VBO

    for(auto obj:objects){
        obj.cleanup();
    }
  glDeleteProgram(programID);
  return true;
}