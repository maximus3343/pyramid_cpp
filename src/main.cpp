#include "../include/input.hpp"
#include "../include/pyramid.hpp"
#include "../include/renderer.hpp"
#include <GLFW/glfw3.h>

static constexpr int width = 800, height = 800;
static constexpr float fov = 45, near = 0.01f, far = 1000.0f;
// View coordinates.
static constexpr float x = 0.0f, y = 0.0f, z = -3.0f;

int main() {
  // Order of init very important.
  init_GLFW();
  auto window = create_window(width, height, "Pyramid Rendering");
  init_GLEW();

  // Shader program used for Pyramid.
  GLuint shader_program =
      create_shader_program(vertex_shader_source, fragment_shader_source);

  // Pyramid rendering will use shader_program.
  Pyramid t(shader_program);

  // Creates perspective projection matrix, and pass it to shader.
  create_projection_matrix(width, height, fov, near, far, shader_program);
  // Creates view matrix.
  create_view_matrix(x, y, z, shader_program);

  // Rotate the pyramid just a bit before drawn.
  t.rotate(20, {0, 1, 0});
  t.rotate(20, {1, 0, 0});

  // Main loop.
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    process_input(window, t);

    t.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleans up and exits.
  glfwDestroyWindow(window);

  return 0;
}