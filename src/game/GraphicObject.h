#pragma once
#include <vector>
#include <string>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>

struct GraphicObject
{
    GLuint vertexArrayID;
    GLuint vertexBufferID, vertextBufferSize;
    GLuint uvBufferID;
    GLuint textureID, textureSamplerID;
    bool hasTexture;
    //const GLfloat vertex_buffer_data[];
    glm::mat4 M;

    GraphicObject();
    ~GraphicObject();

    bool initializeVAO();
    bool setVertices(std::vector< glm::vec3 >);
    bool setTexture(std::vector< glm::vec2 >, std::string bmpPath);
    void draw();
    // void moveObject();

};
