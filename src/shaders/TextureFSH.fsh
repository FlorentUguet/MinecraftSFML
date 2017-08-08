#version 330 core

// Interpolated values from the vertex shaders
in vec2 coord;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D tex;

void main(){
    // Output color = color of the texture at the specified UV
    color = texture( tex, coord ).rgb;
}
