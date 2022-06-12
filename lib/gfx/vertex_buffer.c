#include <glad/glad.h>
#include "gfx.h"

uint32_t create_vertex_buffer(const void *data, uint32_t size)
{
  uint32_t id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  return id;
}

void bind_vertex_buffer(uint32_t id)
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void unbind_vertex_buffer()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}