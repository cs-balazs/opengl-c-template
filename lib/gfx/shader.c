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

  uint8_t result;
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
 * Parameters type and name can have a maximum summed length of 30 characters.
 * The returned pointer must be freed once the value is not needed. 
*/
char *read_shader(const char *type, const char *name)
{
  char filename[49] = { 0 };
  strncat(filename, "shaders/", 15);
  strncat(filename, type, strlen(type));
  strncat(filename, "/", 2);
  strncat(filename, name, strlen(name));
  strncat(filename, ".glsl", 6);

  return read_file((const char *)filename);
};

void setUniform4f(uint32_t shader, const char *name, float v0, float v1,
                  float v2, float v3)
{
  int32_t location = glGetUniformLocation(shader, "u_Color");
  assert(location != -1);
  glUniform4f(location, v0, v1, v2, v3);
}