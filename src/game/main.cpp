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
		Floor floor1(
		{-20, -20}, 
		{20, 20});
	// Plane wall1(
	// 	{0, -1, 0},
	// 	{1, -1, 0}, 
	// 	{1, 1, 0},		
	// 	{0, 1, 0},
	// 	1.0f);
	// Plane wall2(
	// 	{0, -1, 1},
	// 	{1, -1, 1}, 
	// 	{1, 1, 1},		
	// 	{0, 1, 1},
	// 	1.0f);
	// Plane wall3(
	// 	{0, -1, 2},
	// 	{1, -1, 2}, 
	// 	{1, 1, 2},		
	// 	{0, 1, 2},
	// 	1.0f);
	// Plane wall4(
	// 	{0, -1, 3},
	// 	{1, -1, 3}, 
	// 	{1, 1, 3},		
	// 	{0, 1, 3},
	// 	1.0f);
	// Plane wall5(
	// 	{0, -1, -1},
	// 	{0, -1, -2}, 
	// 	{0, 1, -2},		
	// 	{0, 1, -1},
	// 	1.0f);
	// Plane wall6(
	// 	{1, -1, -1},
	// 	{1, -1, -2}, 
	// 	{1, 1, -2},		
	// 	{1, 1, -1},
	// 	1.0f);
	// Plane wall7(
	// 	{2, -1, -1},
	// 	{2, -1, -2}, 
	// 	{2, 1, -2},		
	// 	{2, 1, -1},
	// 	1.0f);
	Wall wall1({1, 1}, {1, 2});
	Wall wall2({1, 0}, {1, 1});
	Wall wall3({1, 0}, {2, 0});
	Wall wall4({2, 0}, {3, 0});
	Wall wall5({3, 0}, {4, 0});
	Wall wall6({5, 0}, {6, 0});
	Wall wall7({2, 1}, {3, 1});
	Wall wall8({3, 1}, {4, 1});
	Wall wall9({4, 1}, {5, 1});
	Wall wall10({4, 0}, {5, 0});
	Wall wall11({2, 1}, {2, 2});

	Menu test_screen{window, "../src/assets/textures/menu.bmp"};
	do{
		test_screen.updateAnimationLoop();

	} 
	while( test_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );
	Game main_screen{window};
	main_screen.addGraphicObject(floor1);
	main_screen.addGraphicObject(wall1);
	main_screen.addGraphicObject(wall2);
	main_screen.addGraphicObject(wall3);
	main_screen.addGraphicObject(wall4);
	main_screen.addGraphicObject(wall5);
	main_screen.addGraphicObject(wall6);
	main_screen.addGraphicObject(wall7);
	main_screen.addGraphicObject(wall8);
	main_screen.addGraphicObject(wall9);
	main_screen.addGraphicObject(wall10);
	main_screen.addGraphicObject(wall11);
	do{
		main_screen.updateAnimationLoop();
	} 
	while( main_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );

	main_screen.cleanup();
	glfwTerminate();

	return 0;
	
}

