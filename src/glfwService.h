#ifndef GLFWSERVICE_H
#define GLFWSERVICE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Callback to launch when changing the size of window
void framebuffer_size_callback(GLFWwindow* window,int height, int width);
// A function to process the key input of the user
void processInput(GLFWwindow* window);

#endif // GLFWSERVICE_H
