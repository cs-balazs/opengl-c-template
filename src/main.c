#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
  float positions[12] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f,
  };

  uint32_t indicies[6] = {
    0, 1, 2,
    2, 3, 0
  };
  // clang-format on

  uint32_t vertex_array_object_id;
  glGenVertexArrays(1, &vertex_array_object_id);
  glBindVertexArray(vertex_array_object_id);

  uint32_t vertex_buffer =
    create_vertex_buffer(positions, 4 * 2 * sizeof(float));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  uint32_t index_buffer = create_index_buffer(indicies, 6);

  uint32_t shader = create_shader("basic");
  glUseProgram(shader);

  int R = 0;
  int G = 0;
  int B = 0;

  int32_t location = glGetUniformLocation(shader, "u_Color");
  assert(location != -1);
  glUniform4f(location, (((float)R) / 255.0f), (((float)G) / 255.0f),
              (((float)B) / 255.0f), 1.0f);

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    gui_update(&R, &G, &B);

    glUseProgram(shader);
    glUniform4f(location, (((float)R) / 255.0f), (((float)G) / 255.0f),
                (((float)B) / 255.0f), 1.0f);

    glBindVertexArray(vertex_array_object_id);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    gui_render();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glDeleteProgram(shader);
  gui_terminate();
  glfwTerminate();
  return 0;
}