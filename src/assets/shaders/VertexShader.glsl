#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main(){
    mat4 MVP = P * V * M;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    UV = vertexUV;
}

