#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include "gui.h"

void gui_update(float colors[4], float translation[2])
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();

  igBegin("Settings", NULL, ImGuiWindowFlags_None);
  igColorEdit4("Color", colors, ImGuiSliderFlags_None);
  igSliderFloat2("Translation", translation, -250, 250, "%.0f",
                 ImGuiSliderFlags_None);
  igEnd();
}