#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gfx.h"
#include "io.h"

uint32_t compile_shader(unsigned int type, const char *source)
{
  uint32_t id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int32_t result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    uint32_t length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char message[length];
    glGetShaderInfoLog(id, length, &length, message);

    printf("Failed to compile %s shader\n",
           type == GL_VERTEX_SHADER ? "vertex" : "fragment");

    printf("%s\n", message);
    glDeleteShader(id);
    return 0;
  }

  return id;
};

uint32_t create_shader(const char *name)
{
  char *vertex_shader = read_shader("vertex", name);
  char *fragment_shader = read_shader("fragment", name);

  uint32_t program = glCreateProgram();
  uint32_t compiled_vertex_shader =
    compile_shader(GL_VERTEX_SHADER, vertex_shader);
  uint32_t compiled_fragment_shader =
    compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(program, compiled_fragment_shader);
  glAttachShader(program, compiled_vertex_shader);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(compiled_fragment_shader);
  glDeleteShader(compiled_vertex_shader);

  free(vertex_shader);
  free(fragment_shader);
  return program;
};

/**
 * Max length of type should be 17 characters.
 * Max length of name should be 17 characters.
*/
char *read_shader(const char *type, const char *name)
{
  char filename[49] = "shaders/\0";

  uint8_t offset = 8;
  memcpy(filename + offset, type, 17);
  offset += strlen(type);

  filename[offset] = '/';
  offset++;

  memcpy(filename + offset, name, 17);
  offset += strlen(name);

  char glsl[6] = ".glsl\0";
  memcpy(filename + offset, glsl, 6);

  return read_file((const char *)filename);
};

void setUniform4f(uint32_t shader, const char *name, float v0, float v1,
                  float v2, float v3)
{
  int32_t location = glGetUniformLocation(shader, name);
  assert(location != -1);
  glUniform4f(location, v0, v1, v2, v3);
}

void setUniform1i(uint32_t shader, const char *name, int32_t value)
{
  int32_t location = glGetUniformLocation(shader, name);
  assert(location != -1);
  glUniform1i(location, value);
}

void setUniformMat4f(uint32_t shader, const char *name, mat4 *projection_matrix)
{
  int32_t location = glGetUniformLocation(shader, name);
  assert(location != -1);
  glUniformMatrix4fv(location, 1, GL_FALSE, projection_matrix[0][0]);
}