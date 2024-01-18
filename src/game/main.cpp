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
	Plane ceiling(
		{-20, 1, -20},
		{20, 1, -20},
		{20, 1, 20},
		{-20, 1, 20},
		50
	);
	Wall wall1({-1, 4}, {0, 4});
	Wall wall2({0, 4}, {1, 4});
	Wall wall3({1, 4}, {2, 4});
	Wall wall4({2, 4}, {3, 4});
	Wall wall5({-2, 4}, {-1, 4});
	Wall wall6({-3, 4}, {-2, 4});
	Wall wall7({-4, 4}, {-3, 4});
	Wall wall8({3, 4}, {3, 3});
	Wall wall9({3, 3}, {3, 2});
	Wall wall10({3, 2}, {3, 1});
	Wall wall11({3, 1}, {3, 0});
	Wall wall12({2, 0}, {3, 0});
	Wall wall13({1, 0}, {2, 0});
	Wall wall14({0, 0}, {1, 0});
	Wall wall15({0, 0}, {0, -1});
	Wall wall16({0, -1}, {0, -2});
	Wall wall17({0, -2}, {-1, -2});
	Wall wall18({-1, -2}, {-2, -2});
	Wall wall19({-2, -2}, {-2, -3});
	Wall wall20({-2, -3}, {-3, -3});
	Wall wall21({-3, -3}, {-4, -3});
	Wall wall22({-4, -3}, {-5, -3});
	Wall wall23({-5, -3}, {-5, -2});
	Wall wall24({-5, -2}, {-5, -1});
	Wall wall25({-5, -1}, {-5, 0});
	Wall wall26({-5, 0}, {-5, 1});
	Wall wall27({-5, 1}, {-5, 2});
	Wall wall28({-5, 2}, {-4, 2});
	Wall wall29({-4, 2}, {-4, 3});
	Wall wall30({-4, 3}, {-4, 4});
	Wall wall31({0, 2}, {0, 3});
	Wall wall32({-1, 2}, {-1, 3});
	Wall wall33({0, 2}, {-1, 2});
	Wall wall34({0, 3}, {-1, 3});
	Wall wall35({-2, 3}, {-3, 3});
	Wall wall36({-2, 2}, {-2, 3});
	Wall wall37({-3, 2}, {-3, 3});
	Wall wall38({-2, 1}, {-2, 2});
	Wall wall39({-3, 1}, {-3, 2});
	Wall wall40({-2, 0}, {-2, 1});
	Wall wall41({-3, 0}, {-3, 1});
	Wall wall42({-2, -1}, {-2, 0});
	Wall wall43({-3, -1}, {-3, 0});
	Wall wall44({-2, -1}, {-3, -1});
	Game game_screen{window};
	game_screen.addGraphicObject(floor1);
	game_screen.addGraphicObject(wall1);
	game_screen.addGraphicObject(wall2);
	game_screen.addGraphicObject(wall3);
	game_screen.addGraphicObject(wall4);
	game_screen.addGraphicObject(wall5);
	game_screen.addGraphicObject(wall6);
	game_screen.addGraphicObject(wall7);
	game_screen.addGraphicObject(wall7);
	game_screen.addGraphicObject(wall8);
	game_screen.addGraphicObject(wall9);
	game_screen.addGraphicObject(wall10);
	game_screen.addGraphicObject(wall11);
	game_screen.addGraphicObject(wall12);
	game_screen.addGraphicObject(wall13);
	game_screen.addGraphicObject(wall14);
	game_screen.addGraphicObject(wall15);
	game_screen.addGraphicObject(wall16);
	game_screen.addGraphicObject(wall17);
	game_screen.addGraphicObject(wall18);
	game_screen.addGraphicObject(wall19);
	game_screen.addGraphicObject(wall20);
	game_screen.addGraphicObject(wall21);
	game_screen.addGraphicObject(wall22);
	game_screen.addGraphicObject(wall23);
	game_screen.addGraphicObject(wall24);
	game_screen.addGraphicObject(wall25);
	game_screen.addGraphicObject(wall26);
	game_screen.addGraphicObject(wall27);
	game_screen.addGraphicObject(wall28);
	game_screen.addGraphicObject(wall29);
	game_screen.addGraphicObject(wall30);
	game_screen.addGraphicObject(wall31);
	game_screen.addGraphicObject(wall32);
	game_screen.addGraphicObject(wall33);
	game_screen.addGraphicObject(wall34);
	game_screen.addGraphicObject(wall35);
	game_screen.addGraphicObject(wall36);
	game_screen.addGraphicObject(wall37);
	game_screen.addGraphicObject(wall38);
	game_screen.addGraphicObject(wall39);
	game_screen.addGraphicObject(wall40);
	game_screen.addGraphicObject(wall41);
	game_screen.addGraphicObject(wall42);
	game_screen.addGraphicObject(wall43);
	game_screen.addGraphicObject(wall44);

	game_screen.addGraphicObject(ceiling);

	
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

