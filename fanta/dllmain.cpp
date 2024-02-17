#include"source/core/core.h"
DWORD __stdcall OverlayThread()
{
	while (!GetModuleHandleA("d3d9.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(420));
	Hooks::Menu::Initialize();
	return TRUE;
}
DWORD __stdcall MainThread() 
{ 
	pCore->Run();
	return TRUE;
}
BOOL __stdcall DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	static bool m_Attached = false;
	if ((hReasons == DLL_PROCESS_ATTACH) && !m_Attached)
	{
		void* func_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
		void* overlay_thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OverlayThread, 0, 0, 0);
		if (func_thread && overlay_thread) { CloseHandle(func_thread); CloseHandle(overlay_thread);  m_Attached = true; }
	}
	return TRUE;
}