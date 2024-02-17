#include <chrono>
#include"ncc_menu/ncc_menu.h"
#include"directhook/direct.h"
#include"draw/draw.h"
#include"fonts/fonts.h"

enum class OverlayTabs
{
	Aimbot,
	Visuals,
	Misc,
	Configs
};

class Overlay
{
public:
	std::string m_szMenuTitle = "Fanta";
	int m_iWidth = 450;
	int m_iHeight = 450;
public:
	bool m_bRenderMenu = false;
	bool m_bInitImGui = false;
public:
	void InitStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::StyleColorsDark();

		style.WindowRounding = 4;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.FramePadding = { 6.0f, 6.0f };
		style.ItemSpacing = { 9.0f, 9.0f };
		style.WindowPadding = { 9.0f, 9.0f };
		style.ItemInnerSpacing = { 8.0f, 4.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 1;
		style.ScrollbarSize = 12.f;
		style.GrabMinSize = 8.f;
		//style.WindowShadowSize = 0.f;

		//style.Colors[ImGuiCol_WindowShadow] = Hex(0xDB4141, 1.0f); // 0x5E61BA

		style.Colors[ImGuiCol_WindowBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = Hex(0x151515, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = Hex(0x191919, 1.0f);

		style.Colors[ImGuiCol_TitleBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = Hex(0x111111, 1.0f);

		style.Colors[ImGuiCol_Border] = Hex(0x1F1F1F, 1.0f);
		style.Colors[ImGuiCol_Separator] = Hex(0x1F1F1F, 1.0f);

		style.Colors[ImGuiCol_SliderGrab] = Hex(0x5500ffd9, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = Hex(0x5500ffd9, 0.8f);

		style.Colors[ImGuiCol_CheckMark] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_Text] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = Hex(0x616161, 1.0f);

		style.Colors[ImGuiCol_Header] = Hex(0x212121, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = Hex(0x444444, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = Hex(0x363636, 1.0f);

		style.Colors[ImGuiCol_FrameBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = Hex(0x111111, 0.9f);
		style.Colors[ImGuiCol_FrameBgActive] = Hex(0x111111, 0.8f);

		style.Colors[ImGuiCol_Button] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = Hex(0x111111, 0.8f);
		style.Colors[ImGuiCol_ButtonActive] = Hex(0x111111, 0.6f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);
	}
	void InitFonts()
	{
		pFonts.Initialize();
	}
}; inline Overlay pOverlay;