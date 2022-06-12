#ifndef GFX_HEADER
#define GFX_HEADER

#include <stdint.h>

// Vertex Buffer
uint32_t create_vertex_buffer(const void *data, uint32_t size);
void bind_vertex_buffer(uint32_t id);
void unbind_vertex_buffer();

// Index Buffer
uint32_t create_index_buffer(const uint32_t *data, uint32_t count);
void bind_index_buffer(uint32_t id);
void unbind_index_buffer();

// Shaders
int compile_shader(unsigned int type, const char *source);
char *read_shader(const char *type, const char *name);
unsigned int create_shader(const char *name);

#endif