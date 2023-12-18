#include "main.h"
#include "window.h"
#include "GraphicObject.h"
#include "Screen.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/controls.hpp>

// Screen startin_screen;

GLFWwindow* window;
// GLuint VertexArrayID, vertexbuffer, vertexbuffer_size, programID;
// GLuint VertexArrayID;
// GLuint vertexbuffer_size;
// GLuint programID;
// GLuint MatrixID, ViewMatrixID, ModelMatrixID;

int main( void )
{	
	window = initializeWindow(1024, 768, "Dungeon Crawler");
	if(!window) return -1;
	Screen main_screen{window};
	GraphicObject boden = GraphicObject();
	//boden.initializeVAO();
	std::vector< glm::vec3 > vertices = std::vector< glm::vec3 >();
	vertices.push_back({ -10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	vertices.push_back({ -10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	vertices.push_back({ -10.0f, -0.8f, 10.0f });
	boden.setVertices(vertices);
	// boden.textureSamplerID = glGetUniformLocation(programID, "myTextureSampler");
	float scaling = 5.0f;
	std::vector< glm::vec2 > uvbufferdata;
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ 0.0f, scaling });
	uvbufferdata.push_back({ scaling, scaling });
	uvbufferdata.push_back({ 0.0f,0.0f });
	uvbufferdata.push_back({ scaling,scaling });
	uvbufferdata.push_back({ scaling,0.0f });
	boden.setTexture(uvbufferdata, "../src/assets/textures/brick_2.bmp");
	// Create and compile our GLSL program from the shaders
	// programID = LoadShaders( "../src/assets/shaders/VertexShader.glsl", "../src/assets/shaders/FragmentShader.glsl" );
	// MatrixID = glGetUniformLocation(programID, "MVP");
	// ViewMatrixID = glGetUniformLocation(programID, "V");
	// ModelMatrixID = glGetUniformLocation(programID, "M");
	main_screen.setGraphicObject(&boden);
	main_screen.loadShaders();
	
	//initializeVertexbuffer();
	do{
		main_screen.updateAnimationLoop();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	// glDeleteBuffers(1, &vertexbuffer);
	// glDeleteVertexArrays(1, &VertexArrayID);
	// glDeleteProgram(programID);
	main_screen.cleanup();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
	
}

// bool initializeWindow(int width, int height, const char * screen_title){
// 	if( !glfwInit() )
// 	{
// 		fprintf( stderr, "Failed to initialize GLFW\n" );
// 		getchar();
// 		return false;
// 	}


// 	glfwWindowHint(GLFW_SAMPLES, 4);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 	// Open a window and create its OpenGL context
// 	window = glfwCreateWindow(width, height, screen_title, NULL, NULL);
// 	if( window == NULL ){
// 		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
// 		getchar();
// 		glfwTerminate();
// 		return false;
// 	}
// 	glfwMakeContextCurrent(window);

// 	// Initialize GLEW
// 	glewExperimental = true; // Needed for core profile
// 	if (glewInit() != GLEW_OK) {
// 		fprintf(stderr, "Failed to initialize GLEW\n");
// 		getchar();
// 		glfwTerminate();
// 		return false;
// 	}

// 	// Ensure we can capture the escape key being pressed below
// 	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
// 	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// 	return true;
// }

// bool initializeVertexbuffer()
// {
//   glGenVertexArrays(1, &VertexArrayID);
//   glBindVertexArray(VertexArrayID);

//   vertexbuffer_size = 2*3;
//   static const GLfloat g_vertex_buffer_data[] = {
//     -10.0f, -0.8f, -10.0f,
// 	10.0f, -0.8f, -10.0f,
// 	10.0f,  -0.8f, 10.0f,
// 	-10.0f, -0.8f, -10.0f,
// 	10.0f,  -0.8f, 10.0f,
// 	-10.0f, -0.8f, 10.0f,
//   };

//   glGenBuffers(1, &vertexbuffer);
//   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//   return true;
// }

// void updateAnimationLoop(){
			
// 	glClear( GL_COLOR_BUFFER_BIT );

// 	// Use our shader
// 	glUseProgram(programID);
// 	computeMatricesFromInputs();
// 	glm::mat4 ProjectionMatrix = getProjectionMatrix();
// 	glm::mat4 ViewMatrix = getViewMatrix();
// 	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * boden.M;

// 	// Send our transformation to the currently bound shader, 
// 	// in the "MVP" uniform
// 	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
// 	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &boden.M[0][0]);
// 	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

// 	// if(glfwGetKey(window, GLFW_KEY_O)) boden.moveObject();

// 	// // 1rst attribute buffer : vertices
// 	// glEnableVertexAttribArray(0);
// 	// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// 	// glVertexAttribPointer(
// 	// 	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
// 	// 	3,                  // size
// 	// 	GL_FLOAT,           // type
// 	// 	GL_FALSE,           // normalized?
// 	// 	0,                  // stride
// 	// 	(void*)0            // array buffer offset
// 	// );

// 	// // Draw the triangle !
// 	// glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

// 	// glDisableVertexAttribArray(0);
// 	boden.draw();
	

// 	// Swap buffers
// 	glfwSwapBuffers(window);
// 	glfwPollEvents();

// }

// bool cleanupVertexbuffer()
// {
//   // Cleanup VBO
//   glDeleteBuffers(1, &boden.vertexBufferID);
//   glDeleteVertexArrays(1, &boden.vertexArrayID);
//   return true;
// }

// bool closeWindow()
// {
//   glfwTerminate();
//   return true;
// }
