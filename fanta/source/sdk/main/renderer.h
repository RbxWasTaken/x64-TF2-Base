#pragma once
#include<array>
#include"../interfaces/interfaces.h"

struct ScreenSize_t {
	int w = 0, h = 0, c = 0;
	void Update() {
		pHl2Interfaces.EngineClient->GetScreenSize(this->w, this->h);
		this->c = (this->w / 2);
	}
}; inline ScreenSize_t pScreenSize;

using byte = unsigned char;
enum Fonts
{
	FONT_ESP,
	//FONT_ESP_OUTLINED,
	FONT_ESP_NAME,
	//FONT_ESP_NAME_OUTLINED,
	FONT_ESP_COND,
	//FONT_ESP_COND_OUTLINED,
	FONT_ESP_PICKUPS,
	//FONT_ESP_PICKUPS_OUTLINED,
	FONT_MENU,
	FONT_INDICATORS,
	FONT_IMGUI,
	FONT_OSRS,

	FONT_ENUM_SIZE // End of the font enum
};

enum EStringAlign {
	ALIGN_DEFAULT,
	ALIGN_CENTER,
	ALIGN_CENTERVERTICAL,
	ALIGN_CENTERHORIZONTAL,
	ALIGN_REVERSE
};

struct Font_t
{
	DWORD dwFont = 0x0;
	const char* szName = nullptr;
	int nTall = 0;
	int nWeight = 0;
	int nFlags = 0;
};

class CRender
{
private:
	class CFont
	{
	public:
		const char* m_szName;
		int m_nTall;
		int m_nWeight;
		int m_nFlags;
		HFont m_hFont;
	};
public:
	std::vector<CFont> m_vecFonts = {};
	std::array<Font_t, FONT_ENUM_SIZE> m_Fonts{};
	const Font_t& GetFont(size_t idx) { return m_Fonts[idx]; }
public:
	bool Initialize();
	void Uninitialize();
public:
	void RemakeFonts()
	{
		m_Fonts[FONT_ESP] = { 0x0, "Tahoma", 12, 200, 0x010 };
	}
	void ReloadFonts()
	{
		for (auto& v : m_Fonts)
		{
			v.dwFont = pHl2Interfaces.VGuiSurface->CreateFont();
			pHl2Interfaces.VGuiSurface->SetFontGlyphSet(v.dwFont, v.szName, v.nTall, v.nWeight, 0, 0, v.nFlags);
		}
	}
public:
	void RenderString(const Font_t& font, int x, int y, Color_t color, const EStringAlign& align, const char* str, ...)
	{
		if (str == nullptr)return;
		va_list va_alist;
		char buffer[1024] = { '\0' };
		wchar_t wstr[1024] = { '\0' };

		va_start(va_alist, str);
		vsprintf_s(buffer, str, va_alist);
		va_end(va_alist);

		wsprintfW(wstr, L"%hs", buffer);
		const auto dwFont = font.dwFont;
		switch (align)
		{
		case ALIGN_DEFAULT: break;
		case ALIGN_CENTER:
			{
			int w = 0, h = 0;
			pHl2Interfaces.VGuiSurface->GetTextSize(dwFont, wstr, w, h);
			x -= (w / 2);
			y -= (h / 2);
			break;
			}
		}

		pHl2Interfaces.VGuiSurface->DrawSetTextPos(x, y);
		pHl2Interfaces.VGuiSurface->DrawSetTextFont(dwFont);
		pHl2Interfaces.VGuiSurface->DrawSetTextColor(color.r, color.g, color.b, color.a);
		pHl2Interfaces.VGuiSurface->DrawPrintText(wstr, wcslen(wstr));
	}
	void RenderLine(const int x, const int y, const int x1, const int y1, const Color_t& clr)
	{
		pHl2Interfaces.VGuiSurface->DrawSetColor(clr);
		pHl2Interfaces.VGuiSurface->DrawLine(x, y, x1, y1);
	}
	void RenderRect(const int x, const int y, const int w, const int h, const Color_t& clr)
	{
		pHl2Interfaces.VGuiSurface->DrawSetColor(clr);
		pHl2Interfaces.VGuiSurface->DrawFilledRect(x, y, x + w, y + h);
	}
}; CRender pRender;