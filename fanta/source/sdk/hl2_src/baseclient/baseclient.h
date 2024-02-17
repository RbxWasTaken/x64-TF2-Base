#include"../../incs/incs.h"
#include"../../../utils/vfunc/vfunc.h"
class CBaseClientDll
{
public:
	CClientClass* GetAllClasses() {
		typedef CClientClass* (__thiscall* Fn)(PVOID);
		return pVirtualFunc.GetVFunc<Fn>(this, 8)(this);
	}
public:
	bool WriteUserCmdDeltaToBuffer(bf_write* buf, int from, int to, bool command) {
		typedef bool(__thiscall* Fn)(PVOID, bf_write*, int, int, bool);
		return pVirtualFunc.GetVFunc<Fn>(this, 23)(this, buf, from, to, command);
	}

	bool GetPlayerView(CViewSetup& playerView) {
		typedef bool(__thiscall* Fn)(PVOID, CViewSetup&);
		return pVirtualFunc.GetVFunc<Fn>(this, 59)(this, playerView);
	}
};