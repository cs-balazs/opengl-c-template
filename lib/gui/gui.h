#ifndef GUI_HEADER
#define GUI_HEADER

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <GLFW/glfw3.h>

static struct ImGuiContext *ctx;
static struct ImGuiIO *io;

void gui_init(GLFWwindow *win);
void gui_terminate();
void gui_render();
void gui_update(float colors[4], float translation[2]);

#endif