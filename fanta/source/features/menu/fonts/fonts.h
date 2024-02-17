#pragma once
#include"../extra/extra.h"
#include"inc/font.h"
#include"inc/icons.h"

class CFonts
{
public:
	ImFont* VerdanaSmall = nullptr;
	ImFont* TitleFont = nullptr;
	ImFont* IconFont = nullptr;
public:
	__inline void Initialize() 
	{
		{
			const auto& io = ImGui::GetIO();
			auto fontConfig = ImFontConfig();
			fontConfig.OversampleH = 2;
			constexpr ImWchar fontRange[]{ 0x0020,0x00FF,0x0400,0x044F, 0 };
			this->VerdanaSmall = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 12.0f, &fontConfig, fontRange);
			this->TitleFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 20.0f, &fontConfig, fontRange);
			constexpr ImWchar IconRange[]{ ICON_MIN_MD, ICON_MAX_MD, 0 };
			ImFontConfig IconConfig;
			IconConfig.MergeMode = true;
			IconConfig.PixelSnapH = true;
			this->IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(MaterialFont_compressed_data, MaterialFont_compressed_size, 12.f, &IconConfig, IconRange);
			io.Fonts->Build();
		}
	}
}; CFonts pFonts;