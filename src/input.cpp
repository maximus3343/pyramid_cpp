#include "../include/input.hpp"

int get_key(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    return GLFW_KEY_W;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    return GLFW_KEY_A;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    return GLFW_KEY_S;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    return GLFW_KEY_D;
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    return GLFW_KEY_Q;
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    return GLFW_KEY_E;
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    return GLFW_KEY_R;
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    return GLFW_KEY_F;
  return 0;
}

void process_input(GLFWwindow *window, Pyramid &pyramid) {
  int key = get_key(window);

  switch (key) {
  case GLFW_KEY_W:
    // Move up.
    pyramid.translate({0.0f, d, 0.0f});
    break;
  case GLFW_KEY_S:
    // Move down.
    pyramid.translate({0.0f, -d, 0.0f});
    break;
  case GLFW_KEY_A:
    // Move left.
    pyramid.translate({-d, 0.0f, 0.0f});
    break;
  case GLFW_KEY_D:
    // Move right.
    pyramid.translate({d, 0.0f, 0.0f});
    break;
  case GLFW_KEY_Q:
    pyramid.rotate(r * 30, {0.0f, 0.0f, 1.0f});
    break;
  case GLFW_KEY_E:
    pyramid.rotate(r * 30, {0.0f, 0.0f, -1.0f});
    break;
  case GLFW_KEY_R:
    pyramid.scale({1.0f, 1.0f, 1.0f + s});
    break;
  case GLFW_KEY_F:
    pyramid.scale({1.0f, 1.0f, 1.0f - s});
    break;
    // No input.
  default:
    break;
  }
}