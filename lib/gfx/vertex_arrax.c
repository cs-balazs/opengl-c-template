#include "gfx.h"
#include <glad/glad.h>
#include <assert.h>

uint32_t opengl_type_size(const uint32_t type)
{
  switch (type) {
  case GL_FLOAT:
    return 4;
  case GL_UNSIGNED_INT:
    return 4;
  case GL_UNSIGNED_BYTE:
    return 2;
  }

  assert(type == GL_FLOAT || type == GL_UNSIGNED_INT ||
         type == GL_UNSIGNED_BYTE);
}

void buffer_layout_add_element(BufferLayout *layout,
                               BufferLayoutElement *element)
{
  layout->elements[layout->length] = *element;
  layout->length++;
  layout->stride += element->count * opengl_type_size(element->type);
}

uint32_t create_vertex_array()
{
  int id;
  glGenVertexArrays(1, &id);
  return id;
}

void vertex_array_add_buffer(const uint32_t vertex_array,
                             const uint32_t vertex_buffer,
                             const BufferLayout *layout)
{
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

  uint64_t offset = 0;
  for (uint32_t i = 0; i < layout->length; i++) {
    const BufferLayoutElement element = (layout->elements[i]);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized,
                          layout->stride, (const void *)offset);

    offset += element.count * opengl_type_size(element.type);
  }
}