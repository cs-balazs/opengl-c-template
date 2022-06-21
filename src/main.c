#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cglm/cglm.h>
#include "window.h"
#include "gui.h"
#include "gfx.h"

int main(void)
{
  GLFWwindow *window = get_window();
  if (window == NULL) {
    return -1;
  }

  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  // clang-format off
  float positions[16] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f,
  };

  uint32_t indicies[6] = {
    0, 1, 2,
    2, 3, 0
  };
  // clang-format on

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  uint32_t vertex_array = create_vertex_array();
  uint32_t vertex_buffer =
    create_vertex_buffer(positions, 4 * 4 * sizeof(float));
  BufferLayout layout = { stride: 0, length: 0 };
  BufferLayoutElement positions_element = { GL_FLOAT, 2, GL_FALSE };
  BufferLayoutElement texture_coordinates_element = { GL_FLOAT, 2, GL_FALSE };

  buffer_layout_add_element(&layout, &positions_element);
  buffer_layout_add_element(&layout, &texture_coordinates_element);
  vertex_array_add_buffer(vertex_array, vertex_buffer, &layout);

  uint32_t index_buffer = create_index_buffer(indicies, 6);

  uint32_t shader = create_shader("basic");
  glUseProgram(shader);

  int R = 0;
  int G = 0;
  int B = 0;

  // setUniform4f(shader, "u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
  setUniform1i(shader, "u_Texture", 0);

  uint32_t texture = create_texture("assets/opengl.png");

  glBindTexture(GL_TEXTURE_2D, texture);

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    gui_update(&R, &G, &B);

    glUseProgram(shader);
    // setUniform4f(shader, "u_Color", (((float)R) / 255.0f),
    //              (((float)G) / 255.0f), (((float)B) / 255.0f), 1.0f);

    glBindVertexArray(vertex_array);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    gui_render();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &index_buffer);
  glDeleteTextures(1, &texture);
  glDeleteProgram(shader);

  gui_terminate();

  glfwTerminate();
  return 0;
}