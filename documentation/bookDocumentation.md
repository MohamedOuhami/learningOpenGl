# Learning OpenGL book documentation

This file represents the documentation for the book "Learning OpenGL" written by Joey De Vries

The book is composed of the following chapters : 
- Getting Started
- Lighting
- Model Loading
- Advanced OpenGL
- Advanced Lighting
- PBR
- In Practice
- 2D Game

## Getting started
- OpenGL is an API that provides us with a set of functions to manipulate graphics and images, but OpenGL itself is not an API but rather a specification
- It just specifies what the result and output of each function should be leaving the developers the freedom on how it should operate
- It's the graphics card manufacturers who develop these functions in different OpenGL versions

### Immediate profile vs Core profile
- In the old days, OpenGL was developed in **immediate mode** or **fixed function pipeline** where most of the functionalitiy was hidden in the library and developers has no idea how the calculations were done
- Now, we use **core profile**, which is really efficient and give us more control, but a bit hard to learn
### Extensions
- OpenGL supports **extensions**, if we have a new or optimized rendering technique, it is implemented in the graphic card's drivers, thus openGL can use this extension without the need to wait for openGL to add It
### State machine
- OpenGL is a large **state machine** : A set of variables that define how openGL should operate
- This state is referred to as **context**
- We have several *state-changing* functions that change some variables in the context, and some *state-using* functions that perform some actions based on the current context
- OpenGL libraries are written in C, and thus it uses an abstraction called **objects**
- An object is a collection of options that represents a subset of OpenGL's state

## Creating a window

- Normally, we would need to create a context, get a window and user input all by ourselves, but luckily there are some libraries that does the dirty work like **SDL,SFML and GLFW**
- In this book, we worked with **GLFW**

### GLFW
- GLFW is library written in C, giving us the bare necessities to create a context, define window parameters, get user input and many more

### GLAD
- OpenGL is just a standard, since there are multiple versions of OpenGL, the location of its function is not known at compile-time, and needs to be queried at run-time
- It is a web service where to define the version of OpenGL and the profile 

## Hello Window
- Most of the notes is in the main.cpp, so to not be redundant, just gonna note things that are not in the code
- Registering the callbacks after we've created the window and before the render loop in initiated

## Hello Triangle
- In OpenGL, everything is in 3D space, but the screen and window is in 2D pixels, so the major work done by OpenGL is to transform the 3D points to 2D arrays of colored pixels
- The process of this transformation is handled by **graphics pipeline** of OpenGL, and it can be divided into 2 major parts : 
        - The first trasforms the 3D coords to 2D coords
        - The seconds transforms the 2D coords into actual colored pixels
- This pipeline has a set of steps which their input is the output of the previous step, and this can be done in a parallel manner
- THe graphics cards have thousands of processing cores that can run small programs called **shaders**
- Shaders are written in **GLSL (OpenGL Shading Language)**
- We pass a list of 3D coordinates for point that form a triangle to graphics pipeline. We'll call this array *Vertex_Data*, this vertex_data is a collection of **vertices**
A vertex is a collection of data per 3D coordinates, this data is presented as *vertex attributes*, and it can hold any data we like, but we're gonna assume that it has 3d coordinates and a color value
- In order for OpenGL to know what to do with the collection of coordinates and color values, we need to specify the **render types** called **hints**, and we have either **GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP** to form either points, triangles and lines

- The progress goes something like this : 
1. The first part is **vertex shader** : It takes as input a single vertex. It has the goal of changing the 3D coordinates into *another type of 3D coordinates that we're going to talk about later*, and it allows us to do some processing on the vertex attributes
2. The **primitive assembly** takes as input all the vertices coming form the vertex shader and assembles all the point into the desired primitive ( triangle or line )
3. The **geometry shader** takes as input the vertices coming from the primitive assembly that form a primitive and has the ability to generate new shapes by emitting new vertices to form new primitives, like creating another triangle from the original triangles
4. The **rasterization stage** : It takes the resulting primitives from the geometry shader and maps them to the corresponding pixels on the final screen, resulting in **fragments** for the **fragment shader** to use It. Before the fragment shader runs, **clipping** is performed which is excluding all fragments that are outside the viewport to improve performance. A fragment == Pixel. Basically, the fragment shader calculates the color of the pixel, and this is where the crazy calculations go on based on the lighting, color etc ...
5. After all the colors were calculated, the final objects passes through one last stage **alpha test and blending**, where we calculate the depth to see how far each object is away from the camera and alpha for its opacity and at the end, It blends everything together

- This looks like a really complex process, but for most project, we only work with the vertex and fragment shader
- In modern OpenGL, we are **required** to implement at least the vertex and fragment shader of our own because the graphics card don't have a default implementation

### Vertex Input
- The NDC coordinates will be transformed to **screen-space coordinates** via the *viewport transform* using the data put in glviewport()
- After setting the vertex_data, we send It to the first process of teh graphics pipeline, *vertex shader*
- We do this by creating memory on the GPU where we store the vertex_data, configure how OpenGL should interpret the memory and specify how to send data to the graphics card, for the vertex shader to process as much vertices as we tell It
- This memory is managed by **vertex buffer objects (VBO)** that stores a large number of vertices in the GPU memory
- The aim of this to send all the vertices in batch and not one by one, so the vertex shader have instant access to all the vertices which makes It fast
- Like specified before objects have an ID representing its address, and a VBO is no different
- For the type of draw in glBufferData, we got : 
        - **GL_STREAM_DRAW** : Data is set only once and used by the GPU at most a few times
        - **GL_STATIC_DRAW** : Data is set only once and used many times
        - **GL_DYNAMIC_DRAW** : Data is changed a lot and used many times

### Vertex Shader
-  Vector In graphics programming we use the mathematical concept of a vector quite often,
since it neatly represents positions/directions in any space and has useful mathematical
properties. A vector in GLSL has a maximum size of 4 and each of its values can
be retrieved via vec.x, vec.y, vec.z and vec.w respectively where each of them
represents a coordinate in space. Note that the vec.w component is not used as a position
in space (we’re dealing with 3D, not 4D) but is used for something called perspective
division. We’ll discuss vectors in much greater depth in a later chapter.
- To see the output of the vertex shader, we have assign the position data to the predefined glPosition which is vec4, that's why we turn into vec4, by adding aPos.w = 1.0

### Fragment Shader
- Fragment shader is all about calculating the color output of the pixels

### Linking vertex attributes
- The vertex shader allows to specify any input we want in the form of vertex attributes, but we need to specify manually which part of the input to be put in the attributes
- If you remember the input, It's a series of floats representing a coordinaets, and three of 3 give one vertex.
- Each float is 4 bytes, that makes It a stride of 12 bytes for each vertex and an offset of 0, they are **tightly packed**, and the first value is at the beginning of the buffer
- This is done with the **glVertexAttribPointer** that takes the following arguments : 
        - 1st : Which vertex attribute we want to configure, and remember that we specified location of the position to 0 in the vertex shader, and since we want to pass the input to the attribute, we set the location to 0
        - 2nd : The size of the vertex attribute. The vertex is of 3 coordinates, so the size is 3
        - 3rd : The type of data in the vertex which is GL_FLOAT
        - 4th : Specify whether we want the data to be normalized to 0,1 or -1, for us it's GL_FALSE
        - 5th : This represents the **stride** or the space between each vertex, and since each vertex is composed of 3 floats, its 3 * sizeof(float), or it can be set to 0 to be calculated automatically under the condition that the vertices are tightly packed, meaning there is no offset between the vertices
        - 6th : A parameter of type (void*), that's why we cast it, representing the offset in which the first value start, for us it's at the beginning so its 0
        i


#### Vertex Array Object
- The previous process seems like a cumbersome process, luckily we have **VAO or Vertex Array Object**
- A VAO can be bound like a normal VBO and any subsequent vertex attributes calls from that point will be stored in the VAO
- This has the advantage that when configuring vertex attribute pointer, we only have to make that call once and whenever we want to draw something, we just bind the corresponding VAOi
- Basically what happens , the VBO gets the vertices data from the CPU to the GPU to make the rendering faster
- After creating the Vertex Shader, we need to tell the GPU from which location or slot to take the attributes from
- So, the step goes by creating the VBO, link It to a buffer
- Create the VAO, and call glVertexAttribPointer, which makes the VAO remember which VBO to match which vertex attributes

#### Element Buffer Objects
- Let's talk abot **Element Buffer Objects** or **EBO**
- Taking the example of wanting to draw a rectangle, we can do that with 2 rectangles, but the thing is that some of the vertices might overlap
- Imagine for a really complex model where we have 1000s of triangles that overlap
- We want to store only the unique vertices, that's where EBO comes for
- EBO is a buffer like VBO that stores the indices that OpenGL uses to decide which vertices to draw.
- This process is called **indexed drawing**
