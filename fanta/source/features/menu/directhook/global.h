#pragma once
#include<Windows.h>
#include<stdint.h>
#include<assert.h>
#include<Psapi.h>
#include"../../../hooking/hooking.h"

#if defined _M_X64
typedef uint64_t uintx_t;
#elif defined _M_IX86
typedef uint32_t uintx_t;
#endif

static uintx_t* MethodsTable = NULL;
struct _DirectXVersion
{
	int Unknown = 0;
	int D3D9 = 1;
}DirectXVersion;

namespace Process
{
	int hProcId;
	HWND hWindow;
	WNDPROC hWndProc;
	HMODULE hModule;
	HANDLE hHandle;
	int WindowWidth;
	int WindowHeight;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}

bool CheckVersion(int _DirectXVersion)
{
	if (_DirectXVersion = DirectXVersion.D3D9) {
		if (GetModuleHandleA("d3d9.dll") != NULL)
			return true;
	}
	return false;
}

WNDCLASSEX WindowClass;
HWND WindowHwnd;

bool InitWindow()
{
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = DefWindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = GetModuleHandle(NULL);
	WindowClass.hIcon = NULL;
	WindowClass.hCursor = NULL;
	WindowClass.hbrBackground = NULL;
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = L"MJ";
	WindowClass.hIconSm = NULL;
	RegisterClassEx(&WindowClass);
	WindowHwnd = CreateWindow(WindowClass.lpszClassName, L"DirectX Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, WindowClass.hInstance, NULL);
	if (WindowHwnd == NULL) {
		return false;
	}
	return true;
}

bool DeleteWindow() {
	DestroyWindow(WindowHwnd);
	UnregisterClassW(WindowClass.lpszClassName, WindowClass.hInstance);
	if (WindowHwnd != NULL)
		return false;
	return true;
}

bool CreateHook(uint16_t nIndex, void** orig, void* func) {
	assert(nIndex >= 0 && orig != NULL && func != NULL);
	void* target = (void*)MethodsTable[nIndex];
	if (MH_CreateHook(target, func, orig) != MH_OK || MH_EnableHook(target) != MH_OK)
		return false;
	return true;
}