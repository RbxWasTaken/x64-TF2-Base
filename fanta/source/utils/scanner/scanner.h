#pragma once
#include<Windows.h>

#define INRANGE(x,a,b)	(x >= a && x <= b)
#define GetBits(x)		(INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetBytes(x)		(GetBits(x[0]) << 4 | GetBits(x[1]))

class CPattern {
private:
	DWORD FindPattern(DWORD64 dwAddress, DWORD64 dwLength, LPCSTR szPattern)
	{
		auto  szPatt = szPattern;
		DWORD64 dwFirstMatch = 0x0;

		DWORD64 dwCur;
		for (dwCur = dwAddress; dwCur < dwLength; dwCur++)
		{
			if (!szPatt)
				return dwFirstMatch;

			const auto& pCurByte = *(BYTE*)dwCur;
			const auto& pBytePatt = *(BYTE*)szPatt;

			if (pBytePatt == '\?' || pCurByte == GetBytes(szPatt))
			{
				if (!dwFirstMatch)
					dwFirstMatch = dwCur;

				if (!szPatt[2])
					return dwFirstMatch;

				szPatt += (pBytePatt == '\?\?' || pBytePatt != '\?') ? 3 : 2;
			}
			else
			{
				szPatt = szPattern;
				dwFirstMatch = 0x0;
			}
		}

		return 0x0;
	}
	HMODULE GetModuleHandleSafe(LPCSTR szModule)
	{
		while (true)
		{
			if (const auto hModule = GetModuleHandleA(szModule))
				return hModule;
			Sleep(10);
		}
	}
public:
	DWORD64 Find(LPCSTR szModule, LPCSTR szPattern)
	{
		if (const auto dwMod = reinterpret_cast<DWORD64>(GetModuleHandleA(szModule)))
		{
			if (const auto& ntHeades = reinterpret_cast<PIMAGE_NT_HEADERS64>(dwMod + reinterpret_cast<PIMAGE_DOS_HEADER>(dwMod)->e_lfanew))
				return FindPattern(dwMod + ntHeades->OptionalHeader.BaseOfCode, dwMod + ntHeades->OptionalHeader.SizeOfCode, szPattern);
		}
	}
}; CPattern pPattern;
class CSignature {
private:
	DWORD64 Address = 0;
	LPCSTR Module = nullptr;
	LPCSTR Pattern = nullptr;
	int Offset = 0;

	void Find()
	{
		Address = pPattern.Find(Module, Pattern);
		if (Address == 0) return;
		Address += Offset;
	}
public:
	CSignature(LPCSTR szModule, LPCSTR szPattern, int iOffset = 0) :
		Module(szModule), Pattern(szPattern), Offset(iOffset) {}
	DWORD64 operator()() {
		if (Address == 0) { Find(); }
		return Address;
	}

	template<typename type>
	__inline type As() { return reinterpret_cast<type>(this->operator()()); }
};


#define MAKE_SIG(name, module, pattern, offset) inline CSignature name{module, pattern, offset}