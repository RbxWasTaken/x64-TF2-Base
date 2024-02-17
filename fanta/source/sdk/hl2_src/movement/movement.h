#pragma once
#include "../../incs/enums.h"
#include "../../incs/classes.h"
class CGameMovement
{
public:
	virtual ~CGameMovement(void) {}
	virtual void ProcessMovement(CBaseEntity* pPlayer, CMoveData* pMove) = 0;
	virtual void StartTrackingPredictionErrors(CBaseEntity* pPlayer) = 0;
	virtual void FinishTrackingPredictionErrors(CBaseEntity* pPlayer) = 0;
	virtual void DiffPrint(char const* fmt, ...) = 0;

	virtual Vec3 GetPlayerMins(bool ducked) const = 0;
	virtual Vec3 GetPlayerMaxs(bool ducked) const = 0;
	virtual Vec3 GetPlayerViewOffset(bool ducked) const = 0;
};