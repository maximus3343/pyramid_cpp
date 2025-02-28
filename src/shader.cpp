#include "../include/shader.hpp"
#include <cstddef>
#include <iostream> // Include for std::cerr

const char *vertex_shader_source = R"glsl(
  #version 330 core
  layout (location = 0) in vec3 aPos;
  layout (location = 1) in vec3 aCol;
  uniform mat4 transform;
  uniform mat4 projection;
  uniform mat4 view;
  out vec3 vertexColor;
  void main(){
      gl_Position = projection*view*transform*vec4(aPos, 1.0);
      vertexColor = aCol;
  }
)glsl";

const char *fragment_shader_source = R"glsl(
  #version 330 core
  out vec4 FragColor; // Output color of the fragment
  in vec3 vertexColor;
  void main() {
    FragColor = vec4(vertexColor, 1.0);
    //FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color (RGBA)
  }
)glsl";

GLuint compile_shader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  // Check for errors.
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader Compilation Error: " << infoLog << std::endl;
  }
  return shader;
}

GLuint create_shader_program(const std::string &vertex_shader_source,
                             const std::string &fragment_shader_source) {
  GLuint vertexShader =
      compile_shader(GL_VERTEX_SHADER, vertex_shader_source.data());
  if (vertexShader == 0)
    return 0; // Check for shader compilation failure

  GLuint fragmentShader =
      compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source.data());
  if (fragmentShader == 0) {
    glDeleteShader(
        vertexShader); // Clean up the vertex shader if fragment shader fails
    return 0;          // Check for shader compilation failure
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check for linking errors.
  GLint success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Program Linking Error: " << infoLog << std::endl;
    glDeleteProgram(shaderProgram); // Clean up the program if linking fails
    return 0;                       // Return 0 to indicate failure
  }

  // Clean up shaders.
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

void create_projection_matrix(int width, int height, float fov, float near,
                              float far, GLuint shader_program) {
  // Creates projection matrix.
  const float aspect = static_cast<float>(width) / static_cast<float>(height);
  auto projection = glm::perspective(glm::radians(fov), aspect, near, far);

  // Put inside the shader.
  GLuint projection_loc = glGetUniformLocation(shader_program, "projection");
  glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));
}

void create_view_matrix(float x, float y, float z, GLuint shader_program) {
  auto view = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

  GLuint view_loc = glGetUniformLocation(shader_program, "view");
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
}
