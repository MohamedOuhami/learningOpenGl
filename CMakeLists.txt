cmake_minimum_required(VERSION 3.16)

# As we're working with a C file, we need to add C in the files
project(LearningOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add glad.c to your sources
add_executable(LearningOpenGL
    src/glad.c
    main.cpp
    src/glfwService.h
)

find_package(OpenGL REQUIRED)

# Make sure this path points to where your glad.h and iKHR directory are located
target_include_directories(LearningOpenGL PRIVATE
    /home/v01d/dev/libs/include
    ${CMAKE_SOURCE_DIR}/src


)

target_link_libraries(LearningOpenGL PRIVATE
    /home/v01d/dev/libs/lib/libglfw3.a
    OpenGL::GL
    X11
    Xrandr
    Xi
    pthread
    dl
    m
)

include(GNUInstallDirs)
install(TARGETS LearningOpenGL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
