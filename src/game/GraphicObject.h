#pragma once
#include <vector>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>

struct GraphicObject
{
    GLuint vertex_array, vertex_buffer, vertext_buffer_size;
    //const GLfloat vertex_buffer_data[];
    glm::mat4 M;

    GraphicObject();
    ~GraphicObject();

    bool initializeVAO();
    bool setVertices(std::vector< glm::vec3 >);
    void draw();

};
