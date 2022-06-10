#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "window.h"
#include "gui.h"

GLFWwindow *get_window()
{
  GLFWwindow *window;

  if (!glfwInit()) {
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf(
      "Failed to initialize OpenGL context, make sure GLAD is linked properly!\n");
    return NULL;
  }

  gui_init(window);

  return window;
}