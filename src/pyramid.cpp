#include "../include/pyramid.hpp"

Pyramid::Pyramid(GLuint shader_program) : _shader_program(shader_program) {
  create_vbo();
  create_vao();
  create_ebo();

  glUseProgram(shader_program);
}

void Pyramid::create_vao() noexcept {
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  // Must be binded before any VAO modification.
  glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);

  // Each vertex data (x,y,z) of two floats.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Sets up RGB colors.
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(1);
  //
}

void Pyramid::create_vbo() noexcept {
  // One for vertices, one for colors.
  glGenBuffers(2, _vbo);
  // Generate vertices.
  glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
               vertices.data(), GL_DYNAMIC_DRAW);
  // Generate colors.
  glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(),
               GL_STATIC_DRAW);
  //
}

void Pyramid::create_ebo() noexcept {
  glGenBuffers(1, &_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
}

void Pyramid::draw() const noexcept {
  // Transform passed to shader each time we wanna draw.
  GLuint transform_loc = glGetUniformLocation(_shader_program, "transform");
  if (transform_loc == -1) {
    std::cerr << "mat4 transform was not found in the shader!" << std::endl;
  }
  glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Pyramid::rotate(float angle, const glm::vec3 &axis) noexcept {
  angle = glm::radians(angle);
  // Axis angle must be normalized.
  rotation = glm::rotate(rotation, angle, glm::normalize(axis));

  // Computes transformation matrix only when rotate, translate or scale is
  // called, not when drawn.
  transform = translation * rotation * scaling;
}

void Pyramid::translate(const glm::vec3 &translate_vec) noexcept {
  translation = glm::translate(translation, translate_vec);

  // Computes transformation matrix only when rotate, translate or scale is
  // called, not when drawn.
  transform = translation * rotation * scaling;
}

void Pyramid::scale(const glm::vec3 &axis) noexcept {
  scaling = glm::scale(scaling, axis);

  // Computes transformation matrix only when rotate, translate or scale is
  // called, not when drawn.
  transform = translation * rotation * scaling;
}