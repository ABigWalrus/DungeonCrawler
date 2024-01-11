#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

GLFWwindow*  initializeWindow(int width, int height, const char * screen_title);
GLuint loadBMP_custom(const char * imagepath);
GLuint loadTGA_glfw(const char *);
GLuint loadDDS(const char *);