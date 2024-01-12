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
    GLuint viewMatrixID, modelMatrixID, projectionMatrixID, visibilityRadiusID;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 initialPosition;
    float horizontalAngle, verticalAngle, initialFoV, mouseSensetivity, speed, mouseSpeed, visibilityRadius;

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

struct MenuScreen{
    GLFWwindow* window;
    GLuint programID;
    GraphicObject background;
    std::vector<GraphicObject> objects;
    MenuScreen(GLFWwindow*, std::string);
    ~MenuScreen();
    void addGraphicObject(GraphicObject&);
    void loadShaders();
    void updateAnimationLoop();
    bool cleanup();
};

class OpenGLScreen{
    public:
        // OpenGLScreen(GLFWwindow*);
        virtual ~OpenGLScreen(){};

        virtual void addGraphicObject(GraphicObject&) = 0;
        virtual void updateAnimationLoop() = 0;
        virtual void cleanup() = 0;
};

class Menu:public OpenGLScreen{
    private:
        GLFWwindow* window;
        GLuint programID;
        std::vector<GraphicObject> objects;
        GraphicObject background;

    public:
        Menu(GLFWwindow*, std::string);
        virtual ~Menu();

        void addGraphicObject(GraphicObject&) override;
        void updateAnimationLoop() override;
        void cleanup() override;
};

class Game:public OpenGLScreen{
    private:
        GLFWwindow* window;
        std::vector<GraphicObject> objects;

        GLuint programID, viewMatrixID, modelMatrixID, projectionMatrixID, visibilityRadiusID;
        
        glm::vec3 initialPosition;
        float horizontalAngle, verticalAngle, initialFoV, mouseSensetivity, speed, mouseSpeed, visibilityRadius;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;
    public:
        Game(GLFWwindow*);
        virtual ~Game();

        void addGraphicObject(GraphicObject&) override;
        void updateAnimationLoop() override;
        void cleanup() override;

        void computeMatricesFromInputs();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
};