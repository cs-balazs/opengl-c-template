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
     50.0f, 150.0f, 0.0f, 0.0f,
    450.0f, 150.0f, 1.0f, 0.0f,
    450.0f, 350.0f, 1.0f, 1.0f,
     50.0f, 350.0f, 0.0f, 1.0f,
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

  mat4 proj;
  glm_ortho(0.0f, 500.0f, 0.0f, 500.0f, -1.0f, 1.0f, proj);
  //mat4 view = { {1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} };
  //glm_translate(view, (vec3){ -100, 0, 0 });

  uint32_t shader = create_shader("basic");
  glUseProgram(shader);

  mat4 mvp;
  float translation[2] = { 0 };
  float colors[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

  setUniform4f(shader, "u_Color", colors[0], colors[1], colors[2], colors[3]);

  setUniform1i(shader, "u_Texture", 0);

  uint32_t texture = create_texture("assets/opengl.png");

  glBindTexture(GL_TEXTURE_2D, texture);

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    gui_update(colors, translation);

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){ translation[0], translation[1], 0.0f });

    glm_mat4_mul(proj, model, mvp);
    setUniformMat4f(shader, "u_MVP", &mvp);

    glUseProgram(shader);
    setUniform4f(shader, "u_Color", colors[0], colors[1], colors[2], colors[3]);

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