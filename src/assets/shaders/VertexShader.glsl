#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
out float visibility;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform float visibilityRadius;

void main(){
    mat4 MVP = P * V * M;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    // if((gl_Position.x*vertexPosition_modelspace.x) + (gl_Position.z) * (gl_Position.z) < (visibilityRadius * visibilityRadius * visibilityRadius)){
    //     visibility = 1;
    // }else{
    //     visibility = -1;
    // }
    // if((visibilityRadius*visibilityRadius) < ((gl_Position.z * gl_Position.z) + (gl_Position.x * gl_Position.x) + (gl_Position.y * gl_Position.y))){
    //     visibility = 0;
    //     // visibility =  visibilityRadius*visibilityRadius/((gl_Position.z * gl_Position.z) + (gl_Position.x * gl_Position.x));
    // }else{
        
    // }
    visibility = 1.0;
    // visibility =  visibilityRadius*visibilityRadius/((gl_Position.z * gl_Position.z) + (gl_Position.x * gl_Position.x) + (gl_Position.y * gl_Position.y));
    // visibility *= 0.10;
    UV = vertexUV;
}

