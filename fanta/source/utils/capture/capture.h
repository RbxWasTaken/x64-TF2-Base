#pragma once
#include<Windows.h>

class Capture
{
private:
	typedef void* (*Interface)();
	struct Interface_t
	{
		Interface szInterface;
		PCHAR szInterfaceName;
		Interface_t* szNextInterface;
	};
public:
	template<typename type>
	__inline type CaptureInterface(LPCSTR szModule, PCCH szObject)
	{
		if (const auto hModule = GetModuleHandleA(szModule))
		{
			if (const auto hFactory = reinterpret_cast<void* (__cdecl*)(const char* pName, int* pReturn)>(GetProcAddress(hModule, "CreateInterface"))) {
				return reinterpret_cast<type>(hFactory(szObject, nullptr));
			}
		}
		return nullptr;
	}
}; Capture pCapture;