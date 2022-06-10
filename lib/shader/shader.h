#ifndef SHADERS_HEADER
#define SHADERS_HEADER

#include <GLFW/glfw3.h>

int compile_shader(unsigned int type, const char *source);
char *read_shader(const char *type, const char *name);
unsigned int create_shader(const char *name);

#endif