#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void initialize_imgui(GLFWwindow* window);
void imgui_newframe();
void imgui_render();
