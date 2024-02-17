#pragma once
#include"../../../../hooking/hooking.h"
#include"../../../../features/visuals/visuals.h"
#include"../../../../features/misc/misc.h"
#include"../../../main/renderer.h"

namespace Sigs
{
	MAKE_SIG(StartDrawing, "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14", 0x0);
	MAKE_SIG(FinishDrawing, "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00", 0x0);
}

namespace Hooks 
{
	namespace EngineVGui 
	{
		inline Hook::Table Table;
		namespace Paint 
		{
			using Fn = void(__fastcall*)(void*, void*, int);
			constexpr uint32_t pIndex = 14u;
			void __fastcall Detour(void* rbx, void* rdx, int mode)
			{
				if (!pScreenSize.w || !pScreenSize.h)
					pScreenSize.Update();

				Table.Original<Fn>(pIndex)(rbx, rdx, mode);

				if (!pHl2Interfaces.EngineClient->IsInGame())
					return;

				pVisuals.Run();
				pMisc.Run();
			}
		}
		void Initialize()
		{
			Table.Initialize(pHl2Interfaces.EngineVGui);
			Table.Hook(&Paint::Detour, Paint::pIndex);
		}
	}
}