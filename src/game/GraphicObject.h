#pragma once
#include <vector>
#include <string>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>

struct GraphicObject
{
    GLuint vertexArrayID, vertexBufferID, vertextBufferSize, uvBufferID;
    GLuint textureID, textureSamplerID;
    bool hasTexture;
    glm::mat4 M;

    GraphicObject();
    ~GraphicObject();

    bool initializeVAO();
    bool setVertices(std::vector< glm::vec3 >);
    bool setTexture(std::vector< glm::vec2 >, std::string);
    void draw();
    void cleanup();
};
