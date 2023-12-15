#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <GL/glew.h>
#include <glfw3.h>
GLFWwindow* window;
GLuint VertexArrayID, vertexbuffer, vertexbuffer_size, programID;
// GLuint VertexArrayID;
// GLuint vertexbuffer_size;
// GLuint programID;
GLuint MatrixID, ViewMatrixID, ModelMatrixID;


bool initializeWindow(int width, int height, const char * screen_title);
bool initializeVertexbuffer();
bool cleanupVertexbuffer();
bool closeWindow();
void updateAnimationLoop();

#endif