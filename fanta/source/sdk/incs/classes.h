#pragma once
#include"enums.h"

#include"dt_recv.h"
#include"dt_common.h"
#include "structs.h"
#include"../../utils/utils.h"

typedef unsigned short MaterialVarSym_t;
class ITexture;
class IMaterial;

class MaterialPropertyTypes_t;
class VertexFormat_t;
using CBaseHandle = unsigned long;

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefHandle(const CBaseHandle& handle) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class Vertex_t {
	Vec2 Position;
	Vec2 TexCoord;
	Vertex_t() {}
	Vertex_t(const Vec2& pos, const Vec2& coord = Vec2(0, 0)) { Position = pos; TexCoord = coord; }
	void Init(const Vec2& pos, const Vec2& coord = Vec2(0, 0)) { Position = pos; TexCoord = coord; }
};

class VMatrix {
private:
	Vec3 m[4][4];
public:
	const matrix3x4& As3x4() { return *((const matrix3x4*)this); }
};

class CAttribute {
public:
	void* _pad0;
	std::uint16_t m_nAttributeDefIndex;
	float m_flValue;
	unsigned int _pad1;
public:
	__inline CAttribute(std::uint16_t Index, float Val) { m_nAttributeDefIndex = Index; m_flValue = Val; }
};
class CAttributeList {
public:
	void* _pad0;
	CUtlVector<CAttribute> Attributes;
	__inline void Add(int index, float value) {
		if (Attributes.Count() > 14) return;
		CAttribute Attr(index, value);
		Attributes.AddToTail(Attr);
		
	}
};

class CUserCmd
{
public:
	virtual ~CUserCmd() {};

	int		command_number;
	int		tick_count;
	Vec3	viewangles;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	byte    impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;	// For shared random functions
	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move
	bool	hasbeenpredicted;
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd;
	unsigned int m_crc;
};

typedef void* (*CreateClientClassFn)(int num, int serial);
typedef void* (*CreateEventFn)();

class CViewSetup {
public:
	// left side of view window
	int			x;
	int			m_nUnscaledX;
	// top side of view window
	int			y;
	int			m_nUnscaledY;
	// width of view window
	int			width;
	int			m_nUnscaledWidth;
	// height of view window
	int			height;
	// which eye are we rendering?
	EStereoEye m_eStereoEye;
	int			m_nUnscaledHeight;

	// the rest are only used by 3D views

		// Orthographic projection?
	bool		m_bOrtho;
	// View-space rectangle for ortho projection.
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;

	// horizontal FOV in degrees
	float		fov;
	// horizontal FOV in degrees for in-view model
	float		fovViewmodel;

	// 3D origin of camera
	Vec3		origin;

	// heading of camera (pitch, yaw, roll)
	Vec3		angles;
	// local Z coordinate of near plane of camera
	float		zNear;
	// local Z coordinate of far plane of camera
	float		zFar;

	// local Z coordinate of near plane of camera ( when rendering view model )
	float		zNearViewmodel;
	// local Z coordinate of far plane of camera ( when rendering view model )
	float		zFarViewmodel;

	// set to true if this is to draw into a subrect of the larger screen
	// this really is a hack, but no more than the rest of the way this class is used
	bool		m_bRenderToSubrectOfLargerScreen;

	// The aspect ratio to use for computing the perspective projection matrix
	// (0.0f means use the viewport)
	float		m_flAspectRatio;

	// Controls for off-center projection (needed for poster rendering)
	bool		m_bOffCenter;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;

	// Control that the SFM needs to tell the engine not to do certain post-processing steps
	bool		m_bDoBloomAndToneMapping;

	// Cached mode for certain full-scene per-frame varying state such as sun entity coverage
	bool		m_bCacheFullSceneState;

	// If using VR, the headset calibration will feed you a projection matrix per-eye.
	// This does NOT override the Z range - that will be set up as normal (i.e. the values in this matrix will be ignored).
	bool        m_bViewToProjectionOverride;
	VMatrix     m_ViewToProjection;
};

using EntityHandle_t = CBaseHandle;

class CMoveData
{

};

class CClientClass
{
public:
	CreateClientClassFn pCreateFn;
	CreateEventFn pCreateEventFn;
	char* pNetworkName;
	RecvTable* pRecvTable;
	CClientClass* pNext;
	int ClassId;
public:
	const char* GetName() { return pNetworkName; }
};

typedef struct player_info_t
{
	char name[32];
	int userId;
	char guid[32 + 1];
	uint32_t friendIds;
	char friendsName[32];
};