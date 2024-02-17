#pragma once
extern int GetNetVar(const char*, const char*);
#include"../../utils/netvars/netvars.h"
#include"../../utils/offsets/offsets.h"

class CBaseEntity
{
public:
	inline int& m_iHealth();
	inline int& m_iTeamNum();
};

CBaseEntity* GetLocalPlayer() {
	return *(CBaseEntity**)(pUtilOffsets.client_dll + pUtilOffsets.local_player);
}
CBaseEntity* GetEntityFromList(uintptr_t index) {
	return *(CBaseEntity**)(pUtilOffsets.client_dll + pUtilOffsets.cl_entitylist + (index << 5));
}