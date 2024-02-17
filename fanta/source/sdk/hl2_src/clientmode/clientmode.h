#pragma once
#include"../../../utils/vfunc/vfunc.h"
class CBaseHudChat
{
public:
	inline void Printf(const int iFilter, const char* const fmt, ...)
	{
		pVirtualFunc.GetVFunc<void(__thiscall*)(void*, int, const char*)>(this, 18)(this, iFilter, fmt);
	}
	inline void ChatPrintf(const int iPlayerIndex, const int iFliter, const char* const fmt, ...)
	{
		pVirtualFunc.GetVFunc<void(__thiscall*)(void*, int, int, const char*)>(this, 19)(this, iPlayerIndex, iFliter, fmt);
	}
};

class CClientModeShared
{
public:
	char szPad[28];
	CBaseHudChat* m_pChatElement;
	bool IsChanPanelOutOfFocus()
	{
		void* CHudChat = pVirtualFunc.GetVFunc<void* (__thiscall*)(void*)>(this, 19)(this);
		return (CHudChat && !*(float*)((unsigned long)CHudChat + 0xFC));
	}
};