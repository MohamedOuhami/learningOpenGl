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
