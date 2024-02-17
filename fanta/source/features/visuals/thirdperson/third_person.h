#pragma once
#include"../../../sdk/interfaces/interfaces.h"
#include"../../vars/vars.h"

class ThirdPerson
{
public:
	void ToggleThirdperson()
	{
		static bool bIsInThirdperson = false;
		if (vars::visuals::third_person == true && !bIsInThirdperson)
		{
			pHl2Interfaces.EngineClient->ClientCmd_Unrestricted("thirdperson");
			bIsInThirdperson = true;
		}
		else if (!vars::visuals::third_person && bIsInThirdperson) {
			pHl2Interfaces.EngineClient->ClientCmd_Unrestricted("firstperson");
		}
	}
}; ThirdPerson pThirdPerson;