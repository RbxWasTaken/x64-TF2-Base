#pragma once
#include"../helper/helper.h"

namespace Menu
{
	inline Rect_t Position = { 200, 200, 450, 425 };
	inline const wchar_t* Title = L"Fanta.solutions";
	inline int TitleBarH = 16;

	inline int SpacingX = 8;
	inline int SpacingY = 4;
	inline int SpacingText = 4;

	inline int AltSpacingX = 2;
	inline int AltSpacingY = 2;

	inline int CheckBoxW = 14;
	inline int CheckBoxH = 14;
	inline int CheckBoxFillSize = 3;

	inline int ButtonW = 90;
	inline int ButtonH = 20;

	inline int ButtonWSmall = 70;
	inline int ButtonHSmall = 16;

	inline int ComboBoxW = 90;
	inline int ComboBoxH = 14;

	inline int InputBoxW = 90;
	inline int InputBoxH = 14;
	inline int InputColorBoxW = 30;

	namespace Colors
	{
		inline Color_t OutlineMenu = { 255,0,255,255 };
		inline Color_t FadeBackground = { 15,15,15,200 };
		inline Color_t Windowbackground = { 13,13,13,255 };
	}

	namespace Overlay
	{
		inline Rect_t Pos = { 0,1060,1920,20 };
		inline Rect_t FadePos = { 0,0,1919,1079 };
	}
}