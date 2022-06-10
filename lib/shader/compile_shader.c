#include <glad/glad.h>
#include <stdio.h>
#include "shader.h"

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