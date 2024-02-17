#pragma once
class CGlobals
{
public:
	int m_nLocalIndex = 0;
	bool m_bIsInGame = false;
	bool m_bIsConnected = false;
	bool m_bIsGameUiVisible = false;
}; CGlobals pGlobals;

struct VelFixRecord
{
	Vec3 m_vOrigin;
	int m_nFlags;
	float m_flSimulationTime;
};

struct PlayerCache
{
	Vec3 m_vecOrigin;
	Vec3 m_vecVelocity;
	Vec3 eyePosition;
	int playersPredictedTick;
	bool didDamge;
};

struct DormantData {
	Vec3 Location;
	float LastUpdate = 0.f;
};