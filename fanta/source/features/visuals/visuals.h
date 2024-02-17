#pragma once
#include"../menu/draw/draw.h"
#include"thirdperson/third_person.h"

class Visuals
{
private:
	void Thirdperson() { pThirdPerson.ToggleThirdperson(); }
	void WeaponSway()
	{
		static ConVar* cl_weapon_sway_inter = pHl2Interfaces.Cvar->FindVar("cl_wpn_sway_interp");
		static ConVar* cl_wpn_sway_scale = pHl2Interfaces.Cvar->FindVar("cl_wpn_sway_scale");

		if (cl_weapon_sway_inter || cl_wpn_sway_scale)
		{
			if (vars::visuals::weapon_sway == true)
			{
				cl_weapon_sway_inter->SetValue(5.0f);
				cl_wpn_sway_scale->SetValue(5.0f);
			}
			else
			{
				cl_weapon_sway_inter->SetValue(0.0f);
				cl_wpn_sway_scale->SetValue(0.0f);
			}
		}
	}
	void FlipViewModels()
	{
		static bool bIsEnabled = false;
		static auto cl_flipviewmodels = pHl2Interfaces.Cvar->FindVar("cl_flipviewmodels");
		if (vars::visuals::flip_viewmodels == true)
		{
			bIsEnabled = true;
			cl_flipviewmodels->SetValue(1);
		}
		else
		{
			if (bIsEnabled)
			{
				cl_flipviewmodels->SetValue(0);
				bIsEnabled = false;
			}
		}
	}
public:
	void Run()
	{
		if (!pHl2Interfaces.EngineClient->IsInGame())
			return;

		this->WeaponSway();
		this->FlipViewModels();
	}
public:
	void FpsWindow()
	{
		ImGui::Begin("FPS", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(108, 24));
		ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
		ImGui::End();
	}
	void MainVisuals()
	{
		
	}
}; Visuals pVisuals;