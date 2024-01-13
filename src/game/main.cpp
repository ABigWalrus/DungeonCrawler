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
	int WINDOW_HEIGHT = 768;
	int WINDOW_WIDTH = 1024;
	window = initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dungeon Crawler");
	if(!window) return -1;

	Menu test_screen{window, "../src/assets/textures/menu.bmp"};
	do{
		test_screen.updateAnimationLoop();

	} 
	while( test_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );
	Game main_screen{window};
	Plane plane1(
		{-10000, -768, -15000}, 
		{10000, -768, -15000},
		{10000, -768, 15000},
		{-10000, -768, 15000});
	main_screen.addGraphicObject(plane1);
	do{
		main_screen.updateAnimationLoop();
	} 
	while( main_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );

	main_screen.cleanup();
	glfwTerminate();

	return 0;
	
}

