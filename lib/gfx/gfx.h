#ifndef GFX_HEADER
#define GFX_HEADER

#include <stdint.h>

uint32_t create_vertex_buffer(const void *data, uint32_t size);
void bind_vertex_buffer(uint32_t id);
void unbind_vertex_buffer();

uint32_t create_index_buffer(const uint32_t *data, uint32_t count);
void bind_index_buffer(uint32_t id);
void unbind_index_buffer();

#endif