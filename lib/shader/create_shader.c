#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

unsigned int create_shader(const char *name)
{
  char *vertex_shader = read_shader("vertex", name);
  char *fragment_shader = read_shader("fragment", name);

  unsigned int program = glCreateProgram();
  unsigned int compiled_vertex_shader =
    compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int compiled_fragment_shader =
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
