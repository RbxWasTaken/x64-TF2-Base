#pragma once
#include"../extra/extra.h"
namespace DrawUtils
{
	std::string string_to_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[] pwBuf;
		delete[] pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
	std::wstring ConvertUtf8ToWide(const std::string_view& str)
	{
		int count = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), NULL, 0);
		std::wstring string(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), &string[0], count);
		return string;
	}
}

typedef struct RGBA
{
	DWORD r, g, b, a;
};

class Color {
public:
	RGBA white = { 255,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA Red = { 255,0,0,255 };
	RGBA Blue = { 0,0,255,255 };
}; Color pColor;

class Draw
{
public:
	__inline void DimBackground(int x, int y, ImColor clr)
	{
		auto drawlist = ImGui::GetBackgroundDrawList();
		drawlist->AddRectFilled(ImVec2(x, y), ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), clr);
	}
	__inline void DrawLine(int x, int y, int x1, int y1, RGBA* color)
	{
		auto drawlist = ImGui::GetOverlayDrawList();
		drawlist->AddLine(ImVec2(x, y), ImVec2(x + x1, y + y1), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0f, color->a / 255.0)));
	}
	__inline void DrawCircle(int x, int y, RGBA* color, float size)
	{
		auto drawlist = ImGui::GetOverlayDrawList();
		drawlist->AddCircle(ImVec2(x, y), size, ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0f, color->a / 255.0)), 0);
	}
	__inline void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
	{
		auto drawlist = ImGui::GetOverlayDrawList();
		drawlist->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0f, color->a / 255.0)), thickness);
	}
	__inline void DrawHealthBar(float x, float y, float w, float h, int health)
	{
		auto drawlist = ImGui::GetOverlayDrawList();
		int healthValue = max(0, min(health, 100));
		int barColor = ImColor(min(510 * (100 - healthValue) / 100, 255), min(510 * healthValue / 100, 255), 25, 255);
		drawlist->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0));
		drawlist->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + (((float)h / 100.0f) * (float)health)), barColor, 0.0f, 0);
	}
	__inline void CDrawText(int x, int y, RGBA* color, const wchar_t* str, ...)
	{
		va_list(args);
		va_start(args, str);
		CHAR buffer[256] = {};
		const char* string = reinterpret_cast<const char*>(str);
		vsprintf_s(buffer, string, args);
		va_end(args);

		ImFont a;
		std::string utf_8_1 = std::string(string);
		std::string utf_8_2 = DrawUtils::string_to_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0f, color->a / 255.0)), buffer);
	}
	__inline void CDrawText(int x, int y, RGBA* color, const char* str, ...)
	{
		va_list(args);
		va_start(args, str);
		CHAR buffer[256] = {};
		vsprintf_s(buffer, str, args);
		va_end(args);

		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = DrawUtils::string_to_UTF8(utf_8_1);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0f, color->a / 255.0)), buffer);
	}
	__inline float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* str, ...)
	{
		va_list(args);
		va_start(args, str);
		CHAR buffer[256] = {};
		vsprintf_s(buffer, str, args);
		va_end(args);

		ImDrawList* window = ImGui::GetOverlayDrawList();
		std::stringstream stream(str);
		std::string line;

		float y = 0.0f;
		int i = 0;

		while (std::getline(stream, line))
		{
			ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, buffer);

			if (center)
			{
				window->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);

				window->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), buffer);
			}
			else
			{
				window->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);
				window->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), buffer);

				window->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), buffer);
			}

			y = pos.y + textSize.y * (i + 1);
			i++;
		}
		return y;
	}
}; Draw pDraw;