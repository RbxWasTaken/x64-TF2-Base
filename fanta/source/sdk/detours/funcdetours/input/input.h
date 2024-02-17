#pragma once
#include"../../../../hooking/hooking.h"
namespace Hooks {
	namespace Input {
		inline Hook::Table Table;

		namespace WriteUserCmdDelteToBuffer  {
			using Fn = bool(__fastcall*)(void*, void*, bf_write*, int, int, bool);
			constexpr uint32_t pIndex = 5u;
			bool __fastcall Detour(void* ecx, void* edx, bf_write* buffer, int from, int to, bool isnewcommand) {
				return Table.Original<Fn>(pIndex)(ecx, edx, buffer, from, to, isnewcommand);
			}
		}
		namespace EncodeUserCmdToBuffer  {
			using Fn = void(__fastcall*)(void*, void*, bf_write&, int);
			constexpr uint32_t pIndex = 6u;
			void __fastcall Detour(void* ecx, void* edx, bf_write& buffer, int slot) {
				Table.Original<Fn>(pIndex)(ecx, edx, buffer, slot);
			}
		}
		namespace DecodeUserCmdFromBuffer {
			using Fn = void(__fastcall*)(void*, void*, bf_write&, int);
			constexpr uint32_t pIndex = 7u;
			void __fastcall Detour(void* ecx, void* edx, bf_write& buffer, int slot) {
				Table.Original<Fn>(pIndex)(ecx, edx, buffer, slot);
			}
		};

		namespace GetUserCmd {
			using Fn = CUserCmd * (__fastcall*)(void*, void*, int);
			constexpr uint32_t pIndex = 8u;
			CUserCmd* __fastcall Detour(void* ecx, void* edx, int num) {
				CUserCmd* pCommands = *reinterpret_cast<CUserCmd**>(reinterpret_cast<DWORD>(pHl2Interfaces.Input) + 0x0FC);
				CUserCmd* UserCmd = &pCommands[num % 90];
				return UserCmd;
			}
		}

		void Initialize() {
			Table.Initialize(pHl2Interfaces.Input);
			Table.Hook(&GetUserCmd::Detour, GetUserCmd::pIndex);
		}
	}
}