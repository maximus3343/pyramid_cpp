#include "../include/pyramid.hpp"
#include <GLFW/glfw3.h>
/*
     Handles key input from user. In our case, handles translation, rotation and
   scale of pyramid.
*/

// Constant translation distance.
static constexpr float d = 0.05f;
// Constant that changes rotation speed.
static constexpr float r = 0.05f;
// Constant scale metric.
static constexpr float s = 0.02f;

int get_key(GLFWwindow *window);

// Handles only one key per frame.
void process_input(GLFWwindow *window, Pyramid &pyramid);