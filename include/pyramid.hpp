#pragma once
#include "../include/shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>

/**
 * @class Pyramid
 * @brief A class that represents a 3D pyramid shape for rendering in OpenGL.
 *
 * Encapsulates the functionality required to create and render a
 * pyramid using OpenGL. Handles creation of VBO, VAO and EBO for pyramid
 * geometry. Uses the shader program as argument to Pyramid class.
 *
 * Usage:
 * - Instantiate a Pyramid object.
 * - Call draw() to render the pyramid.
 */
class Pyramid {
public:
  Pyramid(GLuint shader_program);

  // Handles cleanup.
  ~Pyramid() = default;

  /*
    Should be called at each frame to render the pyramid. Handles any
    transformation applied via input.cpp, or via its public transformation
    methods.
  */
  void draw() const noexcept;

  // Rotates the pyramid, along each of the axis.
  void rotate(float angle, const glm::vec3 &axis) noexcept;
  // Translate the pyramid, along each axis in translation vector.
  void translate(const glm::vec3 &translation_vec) noexcept;
  // Scales the pyramid, along each axis.
  void scale(const glm::vec3 &axis) noexcept;

private:
  // Vertices for a pyramid.
  std::array<GLfloat, 15> vertices{
      -0.5f, -0.5f, -0.5f, // Bottom-left.
      0.5f,  -0.5f, -0.5f, // Bottom-right.
      0.5f,  -0.5f, 0.5f,  // Top-right.
      -0.5f, -0.5f, 0.5f,  // Top-left.
      0.0f,  0.5f,  0.0f   // Apex.
  };
  GLuint _vbo[2], _vao, _ebo, _shader_program;

  // Indices used for specific order in which vertices will be drawn.
  const std::array<GLuint, 18> indices{0, 1, 2,  // Base triangle 1.
                                       0, 2, 3,  // Base triangle 2.
                                       0, 1, 4,  // Side triangle 1.
                                       1, 2, 4,  // Side triangle 2.
                                       2, 3, 4,  // Side triangle 3.
                                       3, 0, 4}; // Side triangle 4.

  // Color for each peak of the squared pyramid.
  const std::array<float, 15> colors{
      1.0f, 0.0f, 0.0f, // Red for the top peak.
      0.0f, 1.0f, 0.0f, // Green for the front-left peak.
      0.0f, 0.0f, 1.0f, // Blue for the front-right peak.
      0.0f, 0.5f, 0.5f, // Yellow for the back-right peak.
      1.0f, 0.0f, 1.0f  // Magenta for the back-left peak.
  };

  // Store the cumulative transformations applied.
  glm::mat4 rotation{glm::mat4(1.0f)};
  glm::mat4 translation{glm::mat4(1.0f)};
  glm::mat4 scaling{glm::mat4(1.0f)};
  // Combines all transformations into one.
  glm::mat4 transform{glm::mat4(1.0f)};

  // Creates and binds VBO, vertices and colors.
  void create_vbo() noexcept;
  // Creates and binds VAO.
  void create_vao() noexcept;
  // Creates and bind EBO.
  void create_ebo() noexcept;
};
