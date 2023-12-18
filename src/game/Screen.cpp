#include "GraphicObject.h"
#include "Screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
    object = nullptr;
    programID = -1;
    viewMatrixID = -1;
    matrixID = -1;
    modelMatrixID = -1;
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
    matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
}
// // Initial initialPosition : on +Z
// glm::vec3 initialPosition = glm::vec3( 0, 0, 5 ); 
// // Initial horizontal angle : toward -Z
// float horizontalAngle = 3.14f;
// // Initial vertical angle : none
// float verticalAngle = 0.0f;
// // Initial Field of View
// float initialFoV = 45.0f;
// float mouseSensetivity = 0.3f;

// float speed = 1.0f; // 3 units / second
// float mouseSpeed = 0.005f;
void Screen::setGraphicObject(GraphicObject* new_object){
    object = new_object;
    // (*object).textureSamplerID = glGetUniformLocation(programID, "myTextureSampler");
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
			
	glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programID);
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * object->M;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &object->M[0][0]);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	// if(glfwGetKey(window, GLFW_KEY_O)) boden.moveObject();

	// // 1rst attribute buffer : vertices
	// glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// glVertexAttribPointer(
	// 	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	// 	3,                  // size
	// 	GL_FLOAT,           // type
	// 	GL_FALSE,           // normalized?
	// 	0,                  // stride
	// 	(void*)0            // array buffer offset
	// );

	// // Draw the triangle !
	// glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	// glDisableVertexAttribArray(0);
	object->draw();
	

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

}

bool Screen::cleanup()
{
  // Cleanup VBO

  object->cleanup();
  return true;
}