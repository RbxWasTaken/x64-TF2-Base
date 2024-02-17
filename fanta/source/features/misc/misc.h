#pragma once
#include"../../sdk/interfaces/interfaces.h"
#include"../vars/vars.h"

class Misc
{
private:
	void CheatBypass()
	{
		static bool cheat_enabled = false;
		if (ConVar* sv_cheats = pHl2Interfaces.Cvar->FindVar("sv_cheats"))
		{
			if (vars::misc::sv_cheats == true && sv_cheats)
			{
				sv_cheats->SetValue(1);
				cheat_enabled = true;
			}
			else
			{
				if (cheat_enabled)
				{
					sv_cheats->SetValue(0);
					cheat_enabled = false;
				}
			}
		}
	}
	void MvmRespawn()
	{
		if (!vars::misc::mvm_respawn)
			return;

		if (pHl2Interfaces.EngineVGui->IsGameUIVisible() || pHl2Interfaces.VGuiSurface->IsCursorVisible())
			return;

		auto* kv{ new KeyValues("MVM_Revive_Response") };
		kv->SetInt("accepted", 1);
		pHl2Interfaces.EngineClient->ServerCmdKeyValues(kv);
	}
public:
	void Run()
	{
		if (!pHl2Interfaces.EngineClient->IsInGame())
			return;

		this->CheatBypass();
		this->MvmRespawn();
	}
}; Misc pMisc;