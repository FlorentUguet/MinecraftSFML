#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    //gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition_modelspace,1);
	gl_Position = MVP *  vec4(vertexPosition_modelspace,1);
}
