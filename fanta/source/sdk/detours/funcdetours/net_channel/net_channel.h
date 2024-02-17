#pragma once
#include"../../../../hooking/hooking.h"
#include"../../../interfaces/interfaces.h"

namespace Hooks
{
	namespace NetChannel
	{
		inline Hook::Function Func;

		namespace SentNetMsg{}
		namespace SendDataGame {};
		namespace Shutdown {};

		void Initialize();
	}
}