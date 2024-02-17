#pragma once
#include<WinUser.h>
#include"../../../features/menu/menu.h"
#include"../../interfaces/interfaces.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
namespace WndProc
{
	LRESULT __stdcall Detour(HWND hWindow, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
		if (pOverlay.m_bRenderMenu) {
			ImGui_ImplWin32_WndProcHandler(hWindow, uInt, wParam, lParam);
			return TRUE;
		}
		return CallWindowProc(Process::hWndProc, hWindow, uInt, wParam, lParam);
	}
}