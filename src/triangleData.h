#ifndef TRIANGLEDATA_H
#define TRIANGLEDATA_H

// All of our coordinates and vertices at first should be specified as 3D coordinates
// These coordinates should be written in a range of -1 to 1
// It's called normalized device coordinates

// A triangle has 3 point ,so we define 3 vertices
// The first point is the one at the bottom left, the second is the bottom right and the last is the top
float vertices[] =  {
    -.5f,-.5f,0.0f,
    .5f,-.5f,0.0f,
    0.0f,.5f,0.0f
};

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "// We define the out variable of the fragment shader\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

#endif // TRIANGLEDATA_H
