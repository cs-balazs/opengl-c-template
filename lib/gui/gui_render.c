#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include "gui.h"

void gui_render()
{
  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}