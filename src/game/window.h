#pragma once

#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

GLFWwindow*  initializeWindow(int width, int height, const char * screen_title);
bool initializeVertexbuffer();
void updateAnimationLoop();
bool cleanupVertexbuffer();
bool closeWindow();