// Define the version of the openGL used for the shader
#version 330 core
// The in vec3 aPos means that we declared all the input vertex attributes in the vertex shader
// Since each vertex represents a 3D coordinates, we use vec3, and we name it vec3
// We also set the location of the input variable via layout(location = 0)
layout (location = 0) in vec3 aPos;

void main(void)
{
    // Here, we set the output of the shader or gl_position to the default position and just casted It to vec4 by adding vec4.w = 1.0
    // This is the simplest of all shaders, because we did no processing, we just sent the input to the output of the shader
    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
}
