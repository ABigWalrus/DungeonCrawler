#include "GraphicObject.h"
#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



GraphicObject::GraphicObject(): hasTexture(false), M(glm::mat4(1.0f)){
    // std::cout << "Graphic Object was created\n";
    
    // glGenVertexArrays(1, &vertexArrayID);
}

GraphicObject::~GraphicObject(){}

bool GraphicObject::initializeVAO(){
    glGenVertexArrays(1, &vertexArrayID);
    return true;
}

bool GraphicObject::setVertices(std::vector<glm::vec3> vertices){
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glGenBuffers(1, &vertexBufferID);
    vertextBufferSize = vertices.size() * sizeof(glm::vec3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertextBufferSize, &vertices[0], GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    return true;
}

bool GraphicObject::setTexture(std::vector<glm::vec2> uv_buffer_data, std::string bmpPath){
    hasTexture = true;
    // glGenTextures(1, &textureID);  
    textureID = loadBMP_custom(bmpPath.c_str());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenBuffers(1, &uvBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, uv_buffer_data.size() * sizeof(glm::vec2), &uv_buffer_data[0], GL_STATIC_DRAW);
    return true;
}

void GraphicObject::draw(){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    if(hasTexture){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(textureSamplerID, 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
    glDrawArrays(GL_TRIANGLES, 0, vertextBufferSize); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
}

// void GraphicObject::moveObject(){
    
//     M = M * glm::translate(glm::mat4(), glm::vec3(0.001f, 0.0f, 0.0f));
// }