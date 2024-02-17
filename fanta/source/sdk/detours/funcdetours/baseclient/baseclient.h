#pragma once
#include"../../../../hooking/hooking.h"
namespace Hooks {
	namespace BaseClient {
		inline Hook::Table Table;
		
		namespace LevelInitPreEntity {
			using Fn = void(__fastcall*)(void*, void*, char const*);
			constexpr uint32_t pIndex = 5u;
			void __fastcall Detour(void* rbx, void* rdx, char const* name) { Table.Original<Fn>(pIndex)(rbx, rdx, name); }
		}
		namespace LevelInitPostEntity {
			using Fn = void(__fastcall*)(void*, void*);
			constexpr uint32_t pIndex = 6u;
			void __fastcall Detour(void* rbx, void* rdx) { 
				Table.Original<Fn>(pIndex)(rbx, rdx);  
				pGlobals.m_nLocalIndex = pHl2Interfaces.EngineClient->GetLocalPlayer();
			}
		}

		namespace LevelShutdown {
			using Fn = void(__fastcall*)(void*, void*);
			constexpr uint32_t pIndex = 7u;
			void __fastcall Detour(void* rbx, void* rdx) {
				Table.Original<Fn>(pIndex)(rbx, rdx);
			}
		}

		namespace CreateMove {
			using Fn = void(__fastcall*)(void*, void*, int, float, bool);
			constexpr uint32_t pIndex = 21u;
			void __fastcall Detour(void* rbx, void* rdx, int number, float frametime, bool active) {
				Table.Original<Fn>(pIndex)(rbx, rdx, number, frametime, active);
			}
		}

		namespace FrameStageNotify {
			using Fn = void(__fastcall*)(void*, void*, EClientFrameStage);
			constexpr uint32_t pIndex = 35u;
			void __fastcall Detour(void* rbx, void* rdx, EClientFrameStage curStage) {
				Table.Original<Fn>(pIndex)(rbx, rdx, curStage);
			}
		}

		namespace DispatchUserMessage {
			using Fn = bool(__fastcall*)(void*, void*, UserMessageType, bf_read&);
			constexpr uint32_t pIndex = 36u;
			bool __fastcall Detour(void* rbx, void* rdx, UserMessageType type, bf_read& data) {
				return Table.Original<Fn>(pIndex)(rbx, rdx, type, data);
			}
		}

		void Initialize()
		{
			Table.Initialize(pHl2Interfaces.BaseClientDll);
			Table.Hook(&LevelInitPreEntity::Detour, LevelInitPreEntity::pIndex);		
			Table.Hook(&LevelInitPostEntity::Detour, LevelInitPostEntity::pIndex);
			Table.Hook(&LevelShutdown::Detour, LevelShutdown::pIndex);
			Table.Hook(&FrameStageNotify::Detour, FrameStageNotify::pIndex);
			Table.Hook(&DispatchUserMessage::Detour, DispatchUserMessage::pIndex);
		}
	}
}