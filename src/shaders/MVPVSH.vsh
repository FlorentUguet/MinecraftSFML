#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = MVP *  vec4(aPosition,1);
    UV = aUV;
}
