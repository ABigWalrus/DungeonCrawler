#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <GL/glew.h>
#include <glfw3.h>
GLFWwindow* window;

bool initializeWindow(int width, int height, const char * screen_title);

#endif