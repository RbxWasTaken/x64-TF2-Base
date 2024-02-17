#pragma once
#include"math.h"

struct PlayerInfo_t
{
	// scoreboard information
	char            name[MAX_PLAYER_NAME_LENGTH];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[SIGNED_GUID_LEN + 1];
	// friends identification number
	uint32_t		friendsID;
	// friends name
	char			friendsName[MAX_PLAYER_NAME_LENGTH];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned long	customFiles[MAX_CUSTOM_FILES];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
};

struct Ray_t
{
	VectorAligned vaStartP;
	VectorAligned vaDelta;
	VectorAligned vaStartOffset;
	VectorAligned vaExtents;

	bool IsRay;
	bool IsSwept;

	void Init(const Vec3& source, const Vec3& destination)
	{
		vaDelta = destination - source;

		IsSwept = (vaDelta.LengthSqr() != 0);

		vaExtents.Set();
		IsRay = true;

		vaStartOffset.Set();
		vaStartP = source;
	}

	void Init(const Vec3& source, const Vec3& destination, const Vec3& min, const Vec3& max)
	{
		vaDelta = destination - source;

		IsSwept = (vaDelta.LengthSqr() != 0);

		vaExtents = max - min;
		vaExtents *= 0.5f;
		IsRay = (vaExtents.LengthSqr() < 1e-6);

		vaStartOffset = min + max;

		vaStartOffset *= 0.5f;
		vaStartP = source - vaStartOffset;
		vaStartOffset *= -1.0f;
	}
};