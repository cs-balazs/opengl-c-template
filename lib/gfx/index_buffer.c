#include <glad/glad.h>
#include "gfx.h"

uint32_t create_index_buffer(const uint32_t *data, uint32_t count)
{
  uint32_t id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data,
               GL_STATIC_DRAW);
  return id;
}

void bind_index_buffer(uint32_t id)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void unbind_index_buffer()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}