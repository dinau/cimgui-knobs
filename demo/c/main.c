#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <GL/gl.h>

#include "setupFonts.h"
#include "IconsFontAwesome6.h"
#include "cimgui-knobs.h"

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igSliderFloat igSliderFloat_Str
#define igCheckbox igCheckbox_Str
#define igColorEdit3 igColorEdit3_Str
#define igButton igButton_Str
#endif

//------"
// main
//------"
int main(int argc, char *argv[]) {
    if (!glfwInit())
        return -1;

    // Decide GL+GLSL versions
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    const char *glsl_version = "#version 330";

    // just an extra window hint for resize
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(1024, 400, "CImGui-Knobs with C language 2025/02", NULL, NULL);
    if (!window) {
        printf("Failed to create window! Terminating!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // enable vsync
    glfwSwapInterval(1);

    // check opengl version sdl uses
    printf("opengl version: %s\n", (char *) glGetString(GL_VERSION));

    // setup imgui
    igCreateContext(NULL);

    // set docking
    ImGuiIO *ioptr = igGetIO();
    ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
                                                             //ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
#undef IMGUI_HAS_DOCK
#ifdef IMGUI_HAS_DOCK
    ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
    ioptr->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport / Platform Windows
#endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    igStyleColorsDark(NULL);
    //igStyleColorsClassic(NULL);
    //igStyleColorsLight(NULL);

    bool showDemoWindow = true;
    ImVec4 clearColor = {.x = 0.45f, .y = 0.55f, .z = 0.60f, .w = 1.0f};
    int showWindowDelay = 1;

    setupFonts();

    // main event loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // start imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        igNewFrame();

        if (showDemoWindow)
            igShowDemoWindow(&showDemoWindow);

        // Show CImGui-knobs demo
        {
          char *title = "ImGui: CImGui-Knobs demo with C lang.  2025/02  " ICON_FA_DOG " " ICON_FA_CAT " " ICON_FA_HORSE " " ICON_FA_KIWI_BIRD;
          igBegin(title, NULL, 0);
            igSetWindowFontScale(1.2);
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
            igSetWindowFontScale(1.0);
          igEnd();
        }

        // render
        igRender();
        glfwMakeContextCurrent(window);
        glViewport(0, 0, (int) ioptr->DisplaySize.x, (int) ioptr->DisplaySize.y);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
#ifdef IMGUI_HAS_DOCK
        if (ioptr->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_window = glfwGetCurrentContext();
            igUpdatePlatformWindows();
            igRenderPlatformWindowsDefault(NULL, NULL);
            glfwMakeContextCurrent(backup_current_window);
        }
#endif
        glfwSwapBuffers(window);

        if (showWindowDelay >= 0){ showWindowDelay--; }
        if (showWindowDelay == 0){ glfwShowWindow(window); }
    }

    // clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
