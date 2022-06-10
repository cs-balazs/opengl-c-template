#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include "gui.h"

void gui_update(int *R, int *G, int *B)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();

  igBegin("Color", NULL, ImGuiWindowFlags_None);
  igSliderInt("R", R, 0, 255, "%d", ImGuiSliderFlags_None);
  igSliderInt("G", G, 0, 255, "%d", ImGuiSliderFlags_None);
  igSliderInt("B", B, 0, 255, "%d", ImGuiSliderFlags_None);
  igEnd();
}