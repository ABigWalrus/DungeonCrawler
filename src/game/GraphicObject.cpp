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



GraphicObject::GraphicObject():vertexArrayID(-1), hasTexture(false), M(glm::mat4(1.0f)){}

GraphicObject::~GraphicObject(){}

bool GraphicObject::initializeVAO(){
    if(vertexArrayID == -1){    // Check if vertextArray was initialized
        glGenVertexArrays(1, &vertexArrayID);
    }
    return true;
}

bool GraphicObject::setVertices(std::vector<glm::vec3> vertices){
    this->initializeVAO();
    glBindVertexArray(vertexArrayID);
    glGenBuffers(1, &vertexBufferID);
    vertextBufferSize = vertices.size() * sizeof(glm::vec3);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertextBufferSize, &vertices[0], GL_STATIC_DRAW);
    return true;
}

bool GraphicObject::setTexture(std::vector<glm::vec2> uv_buffer_data, std::string path){
    hasTexture = true;
    // glGenTextures(1, &textureID);
    if(path[path.length() - 3] == 'd' && path[path.length() - 2] == 'd' && path[path.length() - 1] == 's'){
        textureID = loadDDS(path.c_str());
    }
    if(path[path.length() - 3] == 'b' && path[path.length() - 2] == 'm' && path[path.length() - 1] == 'p'){
        textureID = loadBMP_custom(path.c_str());
    }
   	// glPixelStorei(GL_UNPACK_ALIGNMENT,1);	

    // textureID = loadBMP_custom(path.c_str());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);


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
    glDrawArrays(GL_TRIANGLES, 0, vertextBufferSize);
    glDisableVertexAttribArray(0);
}

void GraphicObject::cleanup(){
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
}

Plane::Plane(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, glm::vec3 _p4):
    p1(_p1), 
    p2(_p2),
    p3(_p3), 
    p4(_p4)
    {
    float WINDOW_WIDTH = 1024.0f;
    float WINDOW_HEIGHT = 768.0f;
    // skin = GraphicObject();
    std::vector< glm::vec3 > vertices = std::vector< glm::vec3 >();
    std::cout << " p1 x "<< p1.x << " " << p1.x / WINDOW_WIDTH; 
    std::cout << " p1 y "<< p1.y << " " << p1.y / WINDOW_HEIGHT;
    std::cout << " p1 x "<< p1.z << " " << p1.z / WINDOW_WIDTH;
    std::cout << "\n";
    std::cout << " p2 x "<< p2.x << " " << p2.x / WINDOW_WIDTH; 
    std::cout << " p2 y "<< p2.y << " " << p2.y / WINDOW_HEIGHT;
    std::cout << " p2 x "<< p2.z << " " << p2.z / WINDOW_WIDTH;
    std::cout << "\n";
    std::cout << " p3 x "<< p3.x << " " << p3.x / WINDOW_WIDTH; 
    std::cout << " p3 y "<< p3.y << " " << p3.y / WINDOW_HEIGHT;
    std::cout << " p3 x "<< p3.z << " " << p3.z / WINDOW_WIDTH;
    std::cout << "\n";
    std::cout << " p4 x "<< p4.x << " " << p4.x / WINDOW_WIDTH; 
    std::cout << " p4 y "<< p4.y << " " << p4.y / WINDOW_HEIGHT;
    std::cout << " p4 x "<< p4.z << " " << p4.z / WINDOW_WIDTH;
    std::cout << "\n";
	vertices.push_back({ p1.x / WINDOW_WIDTH, p1.y / WINDOW_HEIGHT, p1.z / WINDOW_WIDTH });
	vertices.push_back({ p2.x / WINDOW_WIDTH, p2.y / WINDOW_HEIGHT, p2.z / WINDOW_WIDTH });
	vertices.push_back({ p3.x / WINDOW_WIDTH, p3.y / WINDOW_HEIGHT, p3.z / WINDOW_WIDTH });
    vertices.push_back({ p1.x / WINDOW_WIDTH, p1.y / WINDOW_HEIGHT, p1.z / WINDOW_WIDTH });
	vertices.push_back({ p3.x / WINDOW_WIDTH, p3.y / WINDOW_HEIGHT, p3.z / WINDOW_WIDTH });
	vertices.push_back({ p4.x / WINDOW_WIDTH, p4.y / WINDOW_HEIGHT, p4.z / WINDOW_WIDTH });
	
    // skin.setVertices(vertices);

    // float scaling = 10.0f;
	// std::vector< glm::vec2 > uvbufferdata;
	// uvbufferdata.push_back({ 0.0f, 0.0f });
	// uvbufferdata.push_back({ scaling,0.0f });
	// uvbufferdata.push_back({ scaling, scaling });
	// uvbufferdata.push_back({ 0.0f, 0.0f });
	// uvbufferdata.push_back({ scaling,scaling });
	// uvbufferdata.push_back({ 0.0f, scaling });
	// skin.setTexture(uvbufferdata, "../src/assets/textures/diffuse.dds");
    // skin = GraphicObject();
	// std::vector< glm::vec3 > vertices = std::vector< glm::vec3 >();
	// vertices.push_back({ -10.0f, -0.8f, -10.0f });
	// vertices.push_back({ 10.0f, -0.8f, -10.0f });
	// vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	// vertices.push_back({ -10.0f, -0.8f, -10.0f });
	// vertices.push_back({ 10.0f,  -0.8f, 10.0f });
	// vertices.push_back({ -10.0f, -0.8f, 10.0f });
	// skin.setVertices(vertices);
    setVertices(vertices);
	float scaling = 10.0f;
	std::vector< glm::vec2 > uvbufferdata;
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ scaling,0.0f });
	uvbufferdata.push_back({ scaling, scaling });
	uvbufferdata.push_back({ 0.0f, 0.0f });
	uvbufferdata.push_back({ scaling,scaling });
	uvbufferdata.push_back({ 0.0f, scaling });
	// skin.setTexture(uvbufferdata, "../src/assets/textures/diffuse.dds");
    setTexture(uvbufferdata, "../src/assets/textures/diffuse.dds");
}

Plane::~Plane(){}

// GraphicObject& Plane::getSkin(){return skin;}