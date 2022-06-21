#include <glad/glad.h>
#include "gfx.h"
#include "image.h"

uint32_t create_texture(const char *name)
{
  stbi_set_flip_vertically_on_load(1);

  int32_t width = 0;
  int32_t height = 0;
  int32_t channels = 0;
  uint8_t *buffer = stbi_load(name, &width, &height, &channels, 4);

  uint32_t id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, buffer);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (buffer) {
    stbi_image_free(buffer);
  }

  return id;
}