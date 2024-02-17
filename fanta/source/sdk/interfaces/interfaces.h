#pragma once
#include"../../utils/capture/capture.h"
#include"../hl2_src/hl2_src.h"
#include "../steam_src/isteamfriends.h"
#include "../steam_src/isteamnetworkingutils.h"
#include"../steam_src/isteamclient.h"
#include"../sigs/sigs.h"
#include<d3d9.h>

#define XASSERTFALSE(x) if (x) { Error(#x); return false; }

class SteamInterfaces 
{
public:
	ISteamFriends* Friends = nullptr;
	ISteamApps* Apps = nullptr;
	ISteamUserStats* UserStats = nullptr;
	ISteamClient* Client = nullptr;
	ISteamUser* User = nullptr;
	ISteamUtils* Utils = nullptr;
	ISteamNetworkingUtils* NetwokingUtils = nullptr;
public:
	__inline void Initialize()
	{
		this->Client = pCapture.CaptureInterface<ISteamClient*>("steamclient.dll", "SteamClient020");
		const HSteamPipe hsNewPipe = this->Client->CreateSteamPipe();
		const HSteamPipe hsNewUser = this->Client->ConnectToGlobalUser(hsNewPipe);	
		this->Friends = this->Client->GetISteamFriends(hsNewUser, hsNewPipe, "SteamFriends017");
		this->Utils = this->Client->GetISteamUtils(hsNewUser, "SteamUtils010");		
		this->Apps = this->Client->GetISteamApps(hsNewUser, hsNewPipe, "STEAMAPPS_INTERFACE_VERSION008");
		this->UserStats = this->Client->GetISteamUserStats(hsNewUser, hsNewPipe, "STEAMUSERSTATS_INTERFACE_VERSION012");
		this->User = this->Client->GetISteamUser(hsNewUser, hsNewPipe, "SteamUser023");
	}
}; SteamInterfaces pSteamInterfaces;

class Hl2Interfaces
{
public:
	CBaseClientDll* BaseClientDll = nullptr;
	CSurface* VGuiSurface = nullptr;
	ICvar* Cvar = nullptr;
	CGlobalVars* GlobalVars = nullptr;
	IDirect3DDevice9* Direct3DDevice;
	IInputSystem* InputSystem = nullptr;
	IInput* Input = nullptr;
	CEngineClient* EngineClient = nullptr;
	CEngineVGui* EngineVGui = nullptr;
	CSurface* Surface = nullptr;
	CClientEntityList* ClientEntityList = nullptr;
	CPanel* VGuiPanel = nullptr;
	CClientModeShared* ClientModeShared = nullptr;
	CUniformRandomStream* UniformStream = nullptr;
	CKeyValueSystem* KeyValueSystem = nullptr;
	CClientDllSharedAppSystems* ClientDllSharedAppSystem = nullptr;
	CGameMovement* GameMovement = nullptr;
	CPrediction* Prediction = nullptr;
public:
	__inline void Initialize()
	{
		this->BaseClientDll = pCapture.CaptureInterface<CBaseClientDll*>("client.dll", "VClient017");
		this->ClientDllSharedAppSystem = pCapture.CaptureInterface<CClientDllSharedAppSystems*>("client.dll", "VClientDllSharedAppSystems001");
		this->ClientEntityList = pCapture.CaptureInterface<CClientEntityList*>("client.dll", "VClientEntityList003");
		this->VGuiSurface = pCapture.CaptureInterface<CSurface*>("vguimatsurface.dll", "VGUI_Surface030");
		this->VGuiPanel = pCapture.CaptureInterface<CPanel*>("vgui2.dll", "VGUI_Panel009");
		this->Cvar = pCapture.CaptureInterface<ICvar*>("vstdlib.dll", "VEngineCvar004");
		this->InputSystem = pCapture.CaptureInterface<IInputSystem*>("inputsystem.dll", "InputSystemVersion001");
		this->EngineClient = pCapture.CaptureInterface<CEngineClient*>("engine.dll", "VEngineClient014");
		this->EngineVGui = pCapture.CaptureInterface<CEngineVGui*>("engine.dll", "VEngineVGui002");
		this->Surface = pCapture.CaptureInterface<CSurface*>("vguimatsurface.dll", "VGUI_Surface030");
		this->UniformStream = pCapture.CaptureInterface<CUniformRandomStream*>("engine.dll", "VEngineRandom001");
	}
}; Hl2Interfaces pHl2Interfaces;