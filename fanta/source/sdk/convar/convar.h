#pragma once
#include"../hl2_src/convar/convar.h"
#include"../interfaces/interfaces.h"
#include"../../utils/fnv1a/fnv1a.h"
class ConVars
{
public:
	ConVar* cl_interp = nullptr;
	ConVar* cl_flipviewmodels = nullptr;
public:
	__inline void Initialize()
	{
		this->cl_interp = pHl2Interfaces.Cvar->FindVar("cl_interp");
		this->cl_flipviewmodels = pHl2Interfaces.Cvar->FindVar("cl_flipviewmodels");

		ConCommandBase* cmdBase = pHl2Interfaces.Cvar->GetCommands();
		while (cmdBase != nullptr)
		{
			constexpr int FCVAR_HIDDEN = (int)EConVarFlags::FCVAR_HIDDEN;
			constexpr int FCVAR_DEVELOPMENT_ONLY = (int)EConVarFlags::FCVAR_DEVELOPMENT_ONLY;
			constexpr int FCVAR_CHEAT = (int)EConVarFlags::FCVAR_CHEAT;
			constexpr int FCVAR_NOT_CONNECTED = (int)EConVarFlags::FCVAR_NOT_CONNECTED;
			cmdBase->m_nFlags &= ~(FCVAR_HIDDEN | FCVAR_DEVELOPMENT_ONLY | FCVAR_CHEAT | FCVAR_NOT_CONNECTED);
			cmdBase = cmdBase->m_pNext;
		}
	}
	ConVar* FindVar(const char* cvarname)
	{
		if (!cvarMap[FNV1A::HashConst(cvarname)]) {
			cvarMap[FNV1A::HashConst(cvarname)] = pHl2Interfaces.Cvar->FindVar(cvarname);
		}
		return cvarMap[FNV1A::HashConst(cvarname)];
	}
private:
	std::unordered_map<std::uint32_t, ConVar*> cvarMap;
}; ConVars pConVars;