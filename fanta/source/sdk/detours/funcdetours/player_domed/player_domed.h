#pragma once
#include"../../../../hooking/hooking.h"
#include<intrin.h>

namespace Hooks
{
	namespace IsPlayerDomed
	{
		inline Hook::Function Func;
		using Fn = bool(__fastcall*)(void*, void*, int);
		bool __fastcall Detour(void* rbx, void* rdx, int iPlayerIndex)
		{
			bool result = Func.Original<Fn>()(rbx, rdx, iPlayerIndex);
			if (!result)
			{
				static const DWORD64 s_pfJumpFrom = pPattern.Find("client.dll", "84 C0 74 21 80 7D");
				static const DWORD64 s_pJumpTo = pPattern.Find("client.dll", "89 45 BC E8 ? ? ? ? 3B");

				if (reinterpret_cast<DWORD64>(_ReturnAddress()) == s_pfJumpFrom)
					*reinterpret_cast<PDWORD>(_ReturnAddress()) = s_pJumpTo;
			}

			return result;
		}

		void Initialize()
		{
			const Fn pIsPlayerDomed = reinterpret_cast<Fn>(pOffsets.m_dwIsPlayerDominated);
			if (pIsPlayerDomed)
				Func.Initialize(pIsPlayerDomed, &Detour);
		}
	}
}