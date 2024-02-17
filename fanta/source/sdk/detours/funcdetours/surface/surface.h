#pragma once
#include"../panel/panel.h"
MAKE_HOOK(CSurface_LockCursor, pVirtualFunc.GetVFuncPtr(pHl2Interfaces.Surface, 62), void, __fastcall, void* rbx, void* rdx);
ENABLE_HOOK(CSurface_LockCursor, void, __fastcall, void* rbx, void* rdx)
{
	Func.Original<FN>()(rbx, rdx);
}
