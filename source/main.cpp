/*
 Copyright (c) 2016 UAA Software
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <imgui/imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <memory>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "tool_framework.hpp"
#include "tool_SPIRVviewer.hpp"
#include <stdlib.h>
#include <fstream>
#include <string>

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace std;
unique_ptr<ToolFramework> framework;

static void setGUIStyle(void)
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.GrabRounding = style.ScrollbarRounding = style.FrameRounding = 2;
    style.WindowRounding = 0;
    style.ItemSpacing.x = 4; style.FramePadding.x = 6;
    style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.84f, 0.84f, 0.84f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.59f, 0.59f, 0.59f, 0.90f);
    style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.15f, 0.15f, 0.15f, 0.09f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.78f, 0.80f, 0.80f, 0.30f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(1.00f, 1.00f, 1.00f, 0.37f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.22f, 0.60f, 0.82f, 0.00f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.88f, 0.88f, 0.88f, 0.45f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.82f, 0.82f, 0.82f, 0.90f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 0.91f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.53f, 0.53f, 0.53f, 0.67f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.53f, 0.53f, 0.53f, 0.82f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.00f, 0.00f, 0.00f, 0.15f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.82f, 0.82f, 0.82f, 0.67f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.82f, 0.82f, 0.82f, 0.67f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.81f, 0.82f, 0.82f, 0.77f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.60f, 0.82f, 0.50f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.22f, 0.60f, 0.82f, 0.70f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_Column]                = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.53f, 0.53f, 0.53f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.65f, 0.22f, 0.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.93f, 0.52f, 0.02f, 0.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.92f, 0.82f, 0.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.22f, 0.60f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.22f);

    ImFontConfig cfg;
    memset(&cfg, 0, sizeof(ImFontConfig));
    cfg.OversampleH = 2;
    cfg.OversampleV = 2;
    cfg.PixelSnapH = true;
    cfg.GlyphExtraSpacing.x = 0.1f;
    cfg.GlyphExtraSpacing.y = 0.0f;

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/DejaVuSansMono.ttf", 20, &cfg);
}

int main(int numArgs, char* arguments[])
{
	framework = make_unique<shaderTool_t>();
	printf("%i \n", numArgs);
	for (int argIter = 0; argIter < numArgs; argIter++)
	{
		printf("%s \n", arguments[argIter]);
	}
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1600, 900, framework->getWindowTitle(), NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);
    setGUIStyle();
    framework->init();

    // Main loop.
    int fbSizeW, fbSizeH;
    bool showDebugTestWindow = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();
        glfwGetFramebufferSize(window, &fbSizeW, &fbSizeH);

        framework->render(fbSizeW, fbSizeH);
        if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT)) {
            showDebugTestWindow = true;
        }
        if (showDebugTestWindow) {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&showDebugTestWindow);
        }

        glViewport(0, 0, fbSizeW, fbSizeH);
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}