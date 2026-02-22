#include <stdio.h>
#include <string.h>
#include "appImGui.h"

#include "cimgui-knobs.h"


//-------------
//--- gui_main
//-------------
void gui_main(Window *window) {

    bool showDemoWindow = true;
    ImVec4 clearColor = {.x = 0.45f, .y = 0.55f, .z = 0.60f, .w = 1.0f};
    int showWindowDelay = 1;

    setupFonts();

    // main event loop
    while (!glfwWindowShouldClose(window->handle)) {
        glfwPollEvents();
        newFrame();

        if (showDemoWindow)
            igShowDemoWindow(&showDemoWindow);

        // Show CImGui-knobs demo
        {
          char *title = "ImGui: CImGui-Knobs demo with C lang.  2025/02  " ICON_FA_DOG " " ICON_FA_CAT " " ICON_FA_HORSE " " ICON_FA_KIWI_BIRD;
          igBegin(title, NULL, 0);
            static float    val1 = 0;
            static float    val2 = 0;
            static float    val3 = 0;
            static float    val4 = 0;
            static int32_t  val5 = 1;
            static float    val6 = 1;

            if (IgKnobFloat("Gain", &val1, -6.0, 6.0, 0.1, "%.1fdB", IgKnobVariant_Tick, 0, 0, 10, -1, -1)) {
              clearColor.x = (val1 + 6) / 12;
            }
            igSameLine (0, -1.0);
            if (IgKnobFloat("Mix", &val2, -1.0, 1.0, 0.1, "%.1f", IgKnobVariant_Stepped, 0, 0, 10, -1, -1)) {
              clearColor.y = (val2 + 1) / 2;
            }
            // Double click to reset
            if (igIsItemActive() && igIsMouseDoubleClicked_Nil(0)) {
              clearColor.y = 0;
              val2 = 0;
            }
            igSameLine (0, -1.0);

            // Custom colors
            ImVec4 colActive = { .x = 255.0, .y = 0,     .z = 0, .w = 0.7};
            ImVec4 colHovered= {.x = 255.0, .y = 0,     .z = 0, .w = 1};
            ImVec4 colButton = {.x = 0,     .y = 255.0, .z = 0, .w = 1};

            igPushStyleColor_Vec4(ImGuiCol_ButtonActive,  colActive);
            igPushStyleColor_Vec4(ImGuiCol_ButtonHovered, colHovered);
            igPushStyleColor_Vec4(ImGuiCol_Button,        colButton);
            // Push/PopStyleColor() for each colors used (namely ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered for primary and ImGuiCol_Framebg for Track)
            if (IgKnobFloat("Pitch", &val3, -6.0, 6.0, 0.1, "%.1f", IgKnobVariant_WiperOnly, 0, 0, 10, -1, -1)) {
              clearColor.z = (val3 + 6.0 ) / 12.0;
            }
            igPopStyleColor(3);
            igSameLine (0, -1.0);

            // Custom min/max angle
            if (IgKnobFloat("Dry", &val4, -6.0, 6.0, 0.1, "%.1f", IgKnobVariant_Stepped, 0, 0, 10, 1.570796, 3.141592)) {
              clearColor.x = (val4 + 6.0 ) / 12.0;
            }
            igSameLine (0, -1.0);

            // Int value
            if (IgKnobInt("Wet", &val5, 1, 10, 0.1, "%i", IgKnobVariant_Stepped, 0, 0, 10, -1, -1)) {
              clearColor.y = val5/ 10.0;
            }
            igSameLine (0, -1.0);

            // Vertical drag only
            if (IgKnobFloat("Vertical", &val6, 0.0, 10.0, 0.1, "%.1f", IgKnobVariant_Space, 0, IgKnobFlags_DragVertical, 10, -1, -1)) {
              clearColor.z = val6 / 10.0 ;
            }

            //
            igNewLine();
            igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
            //
          igEnd();
        }

        // render
        render(window);
    }
}

//------
// main
//------
int main(int argc, char *argv[]) {
  Window *window = createImGui(1024, 768);

  gui_main(window);

  destroyImGui(window);
}
