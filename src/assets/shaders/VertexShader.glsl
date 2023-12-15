#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

out vec3 pos_color;

void main(){

    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    pos_color = vertexPosition_modelspace;
}

