#pragma once
#include"../../../../includes/imgui/imgui.h"
#include"../../../../includes/imgui/imgui_impl_dx9.h"
#include"../../../../includes/imgui/imgui_impl_win32.h"
#include"../../../../includes/imgui/imgui_internal.h"

ImVec4 Hex(int value, float alpha)
{
	float r = (value >> 16) & 0xFF;
	float g = (value >> 8) & 0xFF;
	float b = value & 0xFF;
	return ImVec4(r / 255, g / 255, b / 255, alpha);
}

class ImGuiExtra
{
public:
	__inline bool CheckBox(const char* label, bool* var) { return ImGui::Checkbox(label, var); }
	__inline void Separator() { ImGui::Separator(); }

}; ImGuiExtra* pImGuiExtra;