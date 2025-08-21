#include <iostream>
#include <glfwService.h>
#include <triangleData.h>

using namespace std;


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


 // ====================================================================================
    // Next, we would create the VAO to remember which VBO to link to which vertex attribute
    // =====================================================================================

    // Define the VAO
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);

    // Bind the Buffer
    glBindVertexArray(VAO);

   // ===============================
    // The first step is create a VBO
    // ===============================
    // Create the VBO
    unsigned int VBO;

    // Here, we create a buffer and give It address to the VBO;
    glGenBuffers(1,&VBO);

    // Now , we bind our buffer to a specific type, in our case its GL_ARRAY_BUFFER;
    // From now on, any buffer call we make on type GL_ARRAY_BUFFER will be used to configure to currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    // Now, we copy the vertices data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_vertices),triangle_vertices,GL_STATIC_DRAW);

    // The goal now is to link the vertex attributes to the vertex shader's input
    // The VAO is bounded with the latest bounded Vertex Buffer Object, which is VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);

    // Now, we just enable the vertex attrib array
    // 0 is the vertex attribute location
    glEnableVertexAttribArray(0);

    // Now, we can unbind the VBO cuz we no longer need It
    glBindBuffer(GL_ARRAY_BUFFER,0);

    // Create the EBO
    unsigned int EBO;
    glGenBuffers(1,&EBO);

    // We bind the buffer to GL_ELEMENT_ARRAY_BUFFER to the EBO and put indices in It
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    // ========================
    // Create the Vertex Shader
    // ========================

    // We go on now on the first step of creating a vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // We attach the shader to our vsh source code
    // The vsh code source is in a c string in triangleData.h
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);

    // Compile the shader
    glCompileShader(vertexShader);

    // ===========================
    // Create the Fragment Shader
    // ===========================

    // We do the same now for the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    // Finally we create a shader program which is the final object linking multiple shaders combined
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();


    // Now, we attach the made shaders to the program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    // Link all of the saders
    glLinkProgram(shaderProgram);

    // The result is a program object that we can activate
    // glUseProgram(shaderProgram);

    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES,0,3);
    // Then we proceed to delete the shaders as we no longer need them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // let's analyze the different arguments

    // We don't want to show an image and stop
    // We create a while to keep rendering

    // If the window is not set to close
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        // Normally, the rendering logic would go here
        // To test how things work, we can clear the screen from the color buffer in the previous frame
        // We can set the color with which to fill the screen after clearing the color buffer
        // glClearColor is a "state-changing" function
        glClearColor(.2f,.3f,.3f,1.0f);

        // After setting our vertex data in triangleData.h, we need to pass It to the vertex shader

        // Then we set that we want to clear the color buffer
        // glClear is a "state-using" function
        glClear(GL_COLOR_BUFFER_BIT);
        // draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);

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

void processInput(GLFWwindow* window){

    // Check if the specified key was pressed
    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS){
        // Close the window
        glfwSetWindowShouldClose(window,true);
    }
}
