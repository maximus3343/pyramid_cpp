#include "../include/renderer.hpp"

void init_GLFW() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit(EXIT_FAILURE);
  }

  // Set GLFW window hints (optional).
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set OpenGL version major.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set OpenGL version minor.
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // Use core profile.
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // For MacOS compatibility (not usually needed on Linux).
}

void init_GLEW() {
  // Allow modern OpenGL features
  glewExperimental = GL_TRUE;

  // Initialize GLEW
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err)
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  glEnable(GL_DEPTH_TEST);
}

GLFWwindow *create_window(int width, int height, const std::string &title) {
  auto window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

  if (!window) {
    fprintf(stderr, "Failed to create GLFW window!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  return window;
}