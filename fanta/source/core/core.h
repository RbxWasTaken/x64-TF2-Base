#pragma once
#include<thread>
#include<chrono>
#include"../utils/utils.h"
#include"../sdk/sdk.h"
#include"../sdk/detours/detours.h"
#include"../features/features.h"

class Core
{
public:
	__inline void Run()
	{		
		while (!GetModuleHandleA("engine.dll"))
			std::this_thread::sleep_for(std::chrono::milliseconds(420));

		pHl2Interfaces.Initialize();			
		pUtilOffsets.Initialize();	
		pDetours.Initialize();	
		pRender.RemakeFonts();
		pFeatures.Initialize();
		pHl2Interfaces.EngineClient->ClientCmd_Unrestricted("play vo/items/wheatley_sapper/wheatley_sapper_attached14.mp3");

	}
}; Core* pCore;