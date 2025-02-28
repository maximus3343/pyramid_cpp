#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

/**
    Responsible for managing GLFW, GLEW and the projection matrix, including
   initializing the graphics context and creating the window for rendering.
*/

// Handles GLFW init.
void init_GLFW();

// Handles GLEW init.
void init_GLEW();

// Handles window init.
GLFWwindow *create_window(int width, int height, const std::string &title);