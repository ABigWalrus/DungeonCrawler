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
	int WINDOW_HEIGHT = 1080;
	int WINDOW_WIDTH = 1920;
	window = initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dungeon Crawler");
	if(!window) return -1;

	Menu loading_screen{window, "../src/assets/textures/loading.bmp"};
	loading_screen.updateAnimationLoop();

	Menu menu_screen{window, "../src/assets/textures/menu.bmp"};

	Floor floor1(
		{-20, -20}, 
		{20, 20});
	Wall wall1({-0.5, 0}, {-0.5, 2});
	Wall wall2({-0.5, 2}, {-0.5, 4});
	Wall wall3({0.5, 0}, {0.5, 2});
	Wall wall4({0.5, 2}, {0.5, 4});
	// Wall wall3({1, 0}, {2, 0});
	// Wall wall4({2, 0}, {3, 0});
	// Wall wall5({3, 0}, {4, 0});
	// Wall wall6({5, 0}, {6, 0});
	// Wall wall7({2, 1}, {3, 1});
	// Wall wall8({3, 1}, {4, 1});
	// Wall wall9({4, 1}, {5, 1});
	// Wall wall10({4, 0}, {5, 0});
	// Wall wall11({2, 1}, {2, 2});
	Game game_screen{window};
	game_screen.addGraphicObject(floor1);
	game_screen.addGraphicObject(wall1);
	game_screen.addGraphicObject(wall2);
	game_screen.addGraphicObject(wall3);
	game_screen.addGraphicObject(wall4);
	// game_screen.addGraphicObject(wall5);
	// game_screen.addGraphicObject(wall6);
	// game_screen.addGraphicObject(wall7);
	// game_screen.addGraphicObject(wall8);
	// game_screen.addGraphicObject(wall9);
	// game_screen.addGraphicObject(wall10);
	// game_screen.addGraphicObject(wall11);
	
	do{
		menu_screen.updateAnimationLoop();

	} 
	while( menu_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );

	do{
		game_screen.updateAnimationLoop();
	} 
	while( game_screen.status != CLOSED &&
		   glfwWindowShouldClose(window) == 0 );

	loading_screen.cleanup();
	menu_screen.cleanup();
	game_screen.cleanup();
	glfwTerminate();

	return 0;
	
}

