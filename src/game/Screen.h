#pragma once

#include "GraphicObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

struct Screen{
    GLFWwindow* window;
    GLuint programID;
    GLuint viewMatrixID, modelMatrixID, projectionMatrixID;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 initialPosition;
    float horizontalAngle, verticalAngle, initialFoV, mouseSensetivity, speed, mouseSpeed;

    std::vector<GraphicObject> objects;
    // GraphicObject* object;
    Screen(GLFWwindow*);
    ~Screen();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    // void setGraphicObject(GraphicObject*);
    void addGraphicObject(GraphicObject&);
    void loadShaders();
    void updateAnimationLoop();
    void computeMatricesFromInputs();
    bool cleanup();
};

struct Menu_Screen{
    GLFWwindow* window;
    GLuint programID;
    GLuint projectionMatrixID, viewMatrixID, modelMatrixID;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    float FoV;
    // glm::vec3 initialPosition;
    // float horizontalAngle, verticalAngle, initialFoV, mouseSensetivity, speed, mouseSpeed;

    std::vector<GraphicObject> objects;
    // GraphicObject* object;
    Menu_Screen(GLFWwindow*);
    ~Menu_Screen();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    // void setGraphicObject(GraphicObject*);
    void addGraphicObject(GraphicObject&);
    void loadShaders();
    void updateAnimationLoop();
    // void computeMatricesFromInputs();
    bool cleanup();
};

