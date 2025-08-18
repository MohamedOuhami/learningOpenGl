#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;

void framebuffer_size_callback(GLFWwindow* window,int height, int width);

int main()
{

    // The first step is to instantiate the GLFW Window
    // Remember that glfw is responsible for handling window creation, user input etc ...
    glfwInit();

    // Now, we can configure GLFW using glfwWindowHint
    // The first argument is the option we want to set, and the second is the actual values

    // We set that the version we want to use 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    // We set the profile to use to be the core one
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // Next, we create a window object and it holds all the windowing data
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);

    // If we failed to create the window
    if (window == NULL){
        cout << "Failed to create the GLFW window" << endl;

        // Terminate GLFW
        glfwTerminate();
        return -1;
    }

    // Make the context of the window, the current context of the thread
    glfwMakeContextCurrent(window);

    // Remember that GLAD is used to point to GLFW function at compile-time
    // We need to initialize GLAD before we call GLFW functions

    // We pass GLAD the function to load the address of the OpenGL functions pointers
    // GLFW has glfwgetprocaddress that defines the correct functions based on the OS
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cout << "Failed to launch GLAD" << endl;
        return -1;
    }

    // We have to set now the size of the rendering window
    // The 1st and 2nd argument is for the location of the lower left corner of the window, 3rd is for the height and 4th for the width
    glViewport(0,0,800,600);

    // But until now, if a user resizes the screen, the viewport would be the same
    // We create a callback function to call whenever the screen gets resized
    // The declaration is in the windowcreation.h file and defined here in the framebuffer_size_callback function

    // Now, we tell glfw to reset the viewpor whenever the window gets resized
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    // We don't want to show an image and stop
    // We create a while to keep rendering

    // If the window is not set to close
    while(!glfwWindowShouldClose(window)){

        // This func will swap the color buffer and show the colors in the screen
        glfwSwapBuffers(window);

        // Process the unhandled events
        glfwPollEvents();
    }

    // When we finish, we want to clean all of teh GLFW resources
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int height, int width){
    glViewport(0,0,height,width);

}

