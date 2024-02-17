#pragma once
#include"../../utils/scanner/scanner.h"

namespace Sigs
{
	MAKE_SIG(GlobalVars_Interface, "engine.dll", "68 ? ? ? ? 50 50 FF 12", 0x1);
	MAKE_SIG(DirectXDeviceEx, "shaderapidx9.dll", "75 22 A1", 0x3);
	MAKE_SIG(Input_Interface, "client.dll", "8B 0D ? ? ? ? 56 8B 01 FF 50 ? 8B 45 ? 5F 5E 5B C7 40", 0x2);
}