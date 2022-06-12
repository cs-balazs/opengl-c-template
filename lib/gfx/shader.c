#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx.h"
#include "io.h"

int compile_shader(unsigned int type, const char *source)
{
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
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