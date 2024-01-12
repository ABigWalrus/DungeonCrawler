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

GLFWwindow* window;


int main( void )
{	
	window = initializeWindow(1024, 768, "Dungeon Crawler");
	if(!window) return -1;
	Menu test_screen{window, "../src/assets/textures/menu.bmp"};

	Screen main_screen{window};
	
	GraphicObject boden = GraphicObject();
	std::vector< glm::vec3 > vertices = std::vector< glm::vec3 >();
	vertices.push_back({ -10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	vertices.push_back({ -10.0f, -0.8f, -10.0f });
	vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	vertices.push_back({ -10.0f, -0.8f, 10.0f });
	boden.setVertices(vertices);

	float scaling = 10.0f;
	std::vector< glm::vec2 > uvbufferdata;
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ scaling,0.0f });
	uvbufferdata.push_back({ scaling, scaling });
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ scaling,scaling });
	uvbufferdata.push_back({ 0.0f, scaling });
	boden.setTexture(uvbufferdata, "../src/assets/textures/diffuse.dds");

	GraphicObject wall = GraphicObject();
	std::vector< glm::vec3 > vertices01 = std::vector< glm::vec3 >();
	vertices01.push_back({ -10.0f, -10.0f, -0.8f });
	vertices01.push_back({ 10.0f, -10.0f, -0.8f });
	vertices01.push_back({ 10.0f, 10.0f,   -0.8f});
	vertices01.push_back({ -10.0f, -10.0f, -0.8f });
	vertices01.push_back({ 10.0f, 10.0f , -0.8f});
	vertices01.push_back({ -10.0f, 10.0f , -0.8f});
	wall.setVertices(vertices01);
	wall.setTexture(uvbufferdata, "../src/assets/textures/brick_2.bmp");
	GraphicObject wall01 = GraphicObject();
	std::vector< glm::vec3 > vertices03 = std::vector< glm::vec3 >();
	vertices03.push_back({ -10.0f, -21.99f, -0.1f });
	vertices03.push_back({ 10.0f, -21.99f, -0.1f });
	vertices03.push_back({ 10.0f, 0.01f,   -0.1f});
	vertices03.push_back({ -10.0f, -21.99f, -0.1f });
	vertices03.push_back({ 10.0f, 0.01f , -0.1f});
	vertices03.push_back({ -10.0f, 0.01f , -0.1f});
	wall01.setVertices(vertices03);
	wall01.setTexture(uvbufferdata, "../src/assets/textures/brick_2.bmp");

	GraphicObject menu = GraphicObject();
	std::vector< glm::vec3 > vertices02 = std::vector< glm::vec3 >();
	vertices02.push_back({ -1.0f, -1.0f, 0.0f });
	vertices02.push_back({ 1.0f, -1.0f, 0.0f });
	vertices02.push_back({ 1.0f, 1.0f, 0.0f});
	vertices02.push_back({ -1.0f, -1.0f, 0.0f });
	vertices02.push_back({ 1.0f, 1.0f , 0.0f});
	vertices02.push_back({ -1.0f, 1.0f , 0.0f});
	menu.setVertices(vertices02);
	
	menu.setTexture(uvbufferdata, "../src/assets/textures/menu.bmp");
	// test_screen.addGraphicObject(menu);	
	main_screen.loadShaders();

	do{
		test_screen.updateAnimationLoop();
	} 
	while( glfwGetKey(window, GLFW_KEY_P ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	main_screen.addGraphicObject(boden);
	main_screen.addGraphicObject(wall);
	main_screen.addGraphicObject(wall01);
	do{
		main_screen.updateAnimationLoop();
	} 
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	main_screen.cleanup();
	glfwTerminate();

	return 0;
	
}

