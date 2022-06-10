#include <string.h>
#include "shader.h"
#include "io.h"

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