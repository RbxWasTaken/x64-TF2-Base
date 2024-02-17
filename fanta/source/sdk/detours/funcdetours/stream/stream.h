#include"../../../interfaces/interfaces.h"
#include"../../../../hooking/hooking.h"
#include"../../../../features/vars/vars.h"

namespace Hooks
{
	namespace RandInt
	{
		inline Hook::Table Table;
		using Fn = int(__thiscall*)(CUniformRandomStream*, int, int);
		constexpr uint32_t pIndex = 2u;

		int __stdcall Detour(int minVal, int maxVal)
		{
			if (vars::misc::flip_medal && pHl2Interfaces.EngineVGui->IsGameUIVisible())
			{
				if (minVal == 0 && maxVal == 9)
					return 0;
			}
			return Table.Original<Fn>(pIndex)(pHl2Interfaces.UniformStream, minVal, maxVal);
		}

		void Initialize()
		{
			Table.Initialize(pHl2Interfaces.UniformStream);
			Table.Hook(&Detour, pIndex);
		}
	}
}