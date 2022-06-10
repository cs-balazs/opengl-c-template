#include <GLFW/glfw3.h>
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include "gui.h"

extern struct ImGuiContext *ctx;
extern struct ImGuiIO *io;

void gui_init(GLFWwindow *win)
{
  // IMGUI_CHECKVERSION();
  ctx = igCreateContext(NULL);
  io = igGetIO();

  const char *glsl_version = "#version 330 core";
  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Setup style
  igStyleColorsDark(NULL);
}