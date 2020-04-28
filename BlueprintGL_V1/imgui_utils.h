#pragma once
#ifndef IMGUI_UTILS_H
#define IMGUI_UTILS_H

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

ImRect ImGui_GetItemRect();
ImRect ImRect_Expanded(const ImRect& rect, float x, float y);

#endif