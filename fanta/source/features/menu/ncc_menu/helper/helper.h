#pragma once
#include<cstdint>
#include<WinUser.h>
#include<chrono>
#include"../../../../sdk/main/renderer.h"

struct Rect_t
{
	int x, y;
	int width, height;
};

Rect_t m_LastWidget = {};
Rect_t m_LastGroupBox = {};
std::wstring m_szCurTip = L"";

class CInputHelper
{
private:
	enum EKeyState {NONE,PRESSED,HELD};
	EKeyState keys[256];
public:
	int m_mouseX, m_mouseY;
public:
	void Update()
	{
		for (int n = 0; n < 256; n++)
		{
			if (GetKeyState(n) & 0x8000)
			{
				if (keys[n] == PRESSED)
					keys[n] = HELD;
				else if (keys[n] != HELD)
					keys[n] = PRESSED;
			}
			else keys[n] = NONE;
		}

		pHl2Interfaces.VGuiSurface->SurfaceGetCursorPos(m_mouseX, m_mouseY);
	}
	bool IsPressed(int16_t key) { return (keys[key] == PRESSED); }
	bool IsHeld(int16_t key) { return (keys[key] == HELD); }
	bool IsPressedAndHeld(int16_t key)
	{
		EKeyState keyState = keys[key];
		static std::chrono::time_point<std::chrono::steady_clock> start[256] = { std::chrono::steady_clock::now() };
		if (keyState == PRESSED) {
			start[key] = std::chrono::steady_clock::now();
			return true;
		}

		if (keyState == HELD && std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - start[key]).count() > 400)
			return true;

		return false;
	}
	void Drag(int mousex, int mousey, int& x, int& y, int w, int h, int offset)
	{
		static POINT delta;
		static bool drag = false;
		static bool move = false;
		bool Held = IsHeld(VK_LBUTTON);

		if ((mousex > x && mousex < x + w && mousey > y - offset && mousey < y - offset + h) && Held)
		{
			drag = true;

			if (!move) {
				delta.x = mousex - x;
				delta.y = mousey - y;
				move = true;
			}
		}

		if (drag) {
			x = mousex - delta.x;
			y = mousey - delta.y;
		}

		if (!Held) {
			drag = false;
			move = false;
		}
	}
	void NullKey(int16_t key) {
		keys[key] = EKeyState::NONE;
	}
}; CInputHelper pInputHelper;