#ifndef GFX_HEADER
#define GFX_HEADER

#include <stdint.h>
#include <cglm/cglm.h>

// Vertex Buffer
uint32_t create_vertex_buffer(const void *data, uint32_t size);
void bind_vertex_buffer(uint32_t id);
void unbind_vertex_buffer();

// Index Buffer
uint32_t create_index_buffer(const uint32_t *data, uint32_t count);
void bind_index_buffer(uint32_t id);
void unbind_index_buffer();

// Vertex Array
typedef struct BufferLayoutElement {
  uint32_t type;
  uint32_t count;
  uint8_t normalized;
} BufferLayoutElement;

typedef struct BufferLayout {
  BufferLayoutElement elements[200];
  uint32_t length;
  uint32_t stride;
} BufferLayout;

void buffer_layout_add_element(BufferLayout *layout,
                               BufferLayoutElement *element);

uint32_t create_vertex_array();
void vertex_array_add_buffer(const uint32_t vertex_array,
                             const uint32_t vertex_buffer,
                             const BufferLayout *layout);

// Shaders
uint32_t compile_shader(uint32_t type, const char *source);
char *read_shader(const char *type, const char *name);
uint32_t create_shader(const char *name);
void setUniform4f(uint32_t shader, const char *name, float v0, float v1,
                  float v2, float v3);
void setUniformMat4f(uint32_t shader, const char *name,
                     mat4 *projection_matrix);
void setUniform1i(uint32_t shader, const char *name, int32_t value);

// Textures
uint32_t create_texture(const char *name);

#endif