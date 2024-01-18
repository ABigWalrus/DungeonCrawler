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

enum SCREEN_STATUS{
    OPEN,
    CLOSED,
    PROCESSING
};
class OpenGLScreen{
    public:
        // OpenGLScreen(GLFWwindow*);
        virtual ~OpenGLScreen(){};

        virtual void addGraphicObject(GraphicObject&) = 0;
        virtual void updateAnimationLoop() = 0;
        virtual void cleanup() = 0;
        virtual void computeMatricesFromInputs() = 0;
};

class Menu:public OpenGLScreen{
    private:
        GLFWwindow* window;
        int height, width;

        GLuint programID;
        std::vector<GraphicObject> objects;
        GraphicObject background;
        
    public:
        SCREEN_STATUS status;

        Menu(GLFWwindow* window, std::string background_texture);
        virtual ~Menu();

        void addGraphicObject(GraphicObject&) override;
        void updateAnimationLoop() override;
        void cleanup() override;
        void computeMatricesFromInputs() override;

};

class Game:public OpenGLScreen{
    private:
        GLFWwindow* window;
        int height, width;
        std::vector<GraphicObject> objects;

        GLuint programID, viewMatrixID, modelMatrixID, projectionMatrixID, torchID, timeID;
        int torch;
        float time;
        glm::vec3 PlayerPosition;
        float horizontalAngle, verticalAngle, initialFoV, mouseSensetivity, speed, mouseSpeed;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;

    public:
        SCREEN_STATUS status;

        Game(GLFWwindow* window);
        virtual ~Game();

        void addGraphicObject(GraphicObject&) override;
        void updateAnimationLoop() override;
        void cleanup() override;
        void computeMatricesFromInputs() override;

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
};