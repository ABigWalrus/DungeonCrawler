#pragma once
#include <vector>
#include <string>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>

class GraphicObject{
    private:
        GLuint vertexArrayID, vertexBufferID, vertextBufferSize, uvBufferID;
        GLuint textureID, textureSamplerID;
    public:
        bool hasTexture;
        glm::mat4 M;
        GraphicObject();
        virtual ~GraphicObject();

        bool initializeVAO();
        bool setVertices(std::vector< glm::vec3 >);
        bool setTexture(std::vector< glm::vec2 >, std::string);
        void draw();
        void cleanup();
};

class Plane:public GraphicObject{
    private:
        glm::vec3 p1, p2, p3, p4;
    public:
        Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float texture_scaling);
        virtual ~Plane();
};

class Floor:public Plane{
    private:
        glm::vec2 p1, p2;
    public:
        Floor(glm::vec2 p1, glm::vec2 p2);
        ~Floor();
};

class Wall:public GraphicObject{
    private:
        glm::vec2 p1, p2;
    public:
        Wall(glm::vec2 p1, glm::vec2 p2);
        ~Wall();
};