#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

/**
 * Header file for shader management.
 */

extern const char *vertex_shader_source;

extern const char *fragment_shader_source;

// Compiles the shader source code.
GLuint compile_shader(GLenum type, const char *source);

// Creates a program out of shader source codes.
GLuint create_shader_program(const std::string &vertex_shader_source,
                             const std::string &fragment_shader_source);

// Creates the projection matrix used inside the shader program.
void create_projection_matrix(int width, int height, float fov, float near,
                              float far, GLuint shader_program);

void create_view_matrix(float x, float y, float z, GLuint shader_program);
