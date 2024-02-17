#pragma once
#include"../../../../sdk/interfaces/interfaces.h"
#include"../../../../hooking/hooking.h"

namespace Hooks
{
	namespace EngineClient
	{
		inline Hook::Table Table;
		namespace isPlayingDemo
		{
			using Fn = bool(__fastcall*)(void*, void*);
			constexpr uint32_t pIndex = 78u;
			bool __fastcall Detour(void* rbx, void* rdx) { return Table.Original<Fn>(pIndex)(rbx, rdx); }
		}

		void Initialize()
		{
			Table.Initialize(pHl2Interfaces.EngineClient);
			Table.Hook(&isPlayingDemo::Detour, isPlayingDemo::pIndex);	
		}
	}
}