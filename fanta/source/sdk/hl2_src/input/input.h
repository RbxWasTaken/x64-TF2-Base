#pragma once
#pragma once
#include <cstdint>
#if !defined( _X360 )
#define INVALID_USER_ID		-1
#else
#define INVALID_USER_ID		XBX_INVALID_USER_ID
#endif
#include "../../steam_src/isteamcontroller.h"
#include "../../incs/bitbuf.h"
#include "../../../utils/vfunc/vfunc.h"
#include"../../incs/classes.h"

struct InputEvent_t
{
	int m_nType;				// Type of the event (see InputEventType_t)
	int m_nTick;				// Tick on which the event occurred
	int m_nData;				// Generic 32-bit data, what it contains depends on the event
	int m_nData2;				// Generic 32-bit data, what it contains depends on the event
	int m_nData3;				// Generic 32-bit data, what it contains depends on the event
};

class ISteamController;

enum ESteamControllerPad;

enum EControllerSource
{
	k_EControllerSource_None,
	k_EControllerSource_LeftTrackpad,
	k_EControllerSource_RightTrackpad,
	k_EControllerSource_Joystick,
	k_EControllerSource_ABXY,
	k_EControllerSource_Switch,
	k_EControllerSource_LeftTrigger,
	k_EControllerSource_RightTrigger,
	k_EControllerSource_Gyro
};

enum EControllerSourceMode
{
	k_EControllerSourceMode_None,
	k_EControllerSourceMode_Dpad,
	k_EControllerSourceMode_Buttons,
	k_EControllerSourceMode_FourButtons,
	k_EControllerSourceMode_AbsoluteMouse,
	k_EControllerSourceMode_RelativeMouse,
	k_EControllerSourceMode_JoystickMove,
	k_EControllerSourceMode_JoystickCamera,
	k_EControllerSourceMode_ScrollWheel,
	k_EControllerSourceMode_Trigger,
	k_EControllerSourceMode_TouchMenu
};

// ControllerHandle_t is used to refer to a specific controller.
// This handle will consistently identify a controller, even if it is disconnected and re-connected
typedef uint64_t ControllerHandle_t;


typedef uint64_t ControllerActionSetHandle_t;
typedef uint64_t ControllerDigitalActionHandle_t;
typedef uint64_t ControllerAnalogActionHandle_t;

#define JOYSTICK_AXIS_INTERNAL( _joystick, _axis ) ( JOYSTICK_FIRST_AXIS + ((_joystick) * MAX_JOYSTICK_AXES) + (_axis) )
#define JOYSTICK_AXIS( _joystick, _axis ) ( (AnalogCode_t)JOYSTICK_AXIS_INTERNAL( _joystick, _axis ) )

enum
{
	MAX_JOYSTICKS = 1,
	MOUSE_BUTTON_COUNT = 5,
	MAX_NOVINT_DEVICES = 2,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum AnalogCode_t
{
	ANALOG_CODE_INVALID = -1,
	MOUSE_X = 0,
	MOUSE_Y,
	MOUSE_XY,		// Invoked when either x or y changes
	MOUSE_WHEEL,

	JOYSTICK_FIRST_AXIS,
	JOYSTICK_LAST_AXIS = JOYSTICK_AXIS_INTERNAL(MAX_JOYSTICKS - 1, MAX_JOYSTICK_AXES - 1),

	ANALOG_CODE_LAST,
};

struct kbutton_t;
struct ButtonCode_t;
struct GameActionSet_t;
struct CameraThirdData_t;
struct GameActionSetFlags_t;
struct C_BaseCombatWeapon;


class IInput
{
public:
	virtual	void			Init_All(void) = 0;
	virtual void			Shutdown_All(void) = 0;
	virtual int				GetButtonBits(int) = 0;
	virtual void			CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool			WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand) = 0;
	virtual void			EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual void			DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual CUserCmd* GetUserCmd(int sequence_number) = 0;
	virtual void			MakeWeaponSelection(C_BaseCombatWeapon* weapon) = 0;
	virtual float			KeyState(kbutton_t* key) = 0;
	virtual int				KeyEvent(int eventcode, ButtonCode_t keynum, const char* pszCurrentBinding) = 0;
	virtual kbutton_t* FindKey(const char* name) = 0;
	virtual void			ControllerCommands(void) = 0;
	virtual void			Joystick_Advanced(void) = 0;
	virtual void			Joystick_SetSampleTime(float frametime) = 0;
	virtual void			IN_SetSampleTime(float frametime) = 0;
	virtual void			AccumulateMouse(void) = 0;
	virtual void			ActivateMouse(void) = 0;
	virtual void			DeactivateMouse(void) = 0;
	virtual void			ClearStates(void) = 0;
	virtual float			GetLookSpring(void) = 0;
	virtual void			GetFullscreenMousePos(int* mx, int* my, int* unclampedx = 0, int* unclampedy = 0) = 0;
	virtual void			SetFullscreenMousePos(int mx, int my) = 0;
	virtual void			ResetMouse(void) = 0;
	virtual	float			GetLastForwardMove(void) = 0;
	virtual	float			Joystick_GetForward(void) = 0;
	virtual	float			Joystick_GetSide(void) = 0;
	virtual	float			Joystick_GetPitch(void) = 0;
	virtual	float			Joystick_GetYaw(void) = 0;
	virtual void			CAM_Think(void) = 0;
	virtual int				CAM_IsThirdPerson(void) = 0;
	virtual void			CAM_ToThirdPerson(void) = 0;
	virtual void			CAM_ToFirstPerson(void) = 0;
	virtual void			CAM_StartMouseMove(void) = 0;
	virtual void			CAM_EndMouseMove(void) = 0;
	virtual void			CAM_StartDistance(void) = 0;
	virtual void			CAM_EndDistance(void) = 0;
	virtual int				CAM_InterceptingMouse(void) = 0;
	virtual void			CAM_ToOrthographic() = 0;
	virtual	bool			CAM_IsOrthographic() const = 0;
	virtual	void			CAM_OrthographicSize(float& w, float& h) const = 0;
	virtual void			SetPreferredGameActionSet(GameActionSet_t action_set) = 0;
	virtual GameActionSet_t GetPreferredGameActionSet() = 0;
	virtual void			SetGameActionSetFlags(GameActionSetFlags_t action_set_flags) = 0;
	virtual void			LevelInit(void) = 0;
	virtual void			ClearInputButton(int bits) = 0;
	virtual	void			CAM_SetCameraThirdData(CameraThirdData_t* pCameraData, const void* vecCameraOffset) = 0;
	virtual void			CAM_CameraThirdThink(void) = 0;
	virtual	bool			EnableJoystickMode() = 0;
	virtual bool			IsSteamControllerActive() = 0;
};

class IInputSystem
{
public:
	virtual void AttachToWindow(void* hWnd) = 0;
	virtual void DetachFromWindow() = 0;
	virtual void EnableInput(bool bEnable) = 0;
	virtual void EnableMessagePump(bool bEnable) = 0;
	virtual void PollInputState() = 0;
	virtual int GetPollTick() const = 0;
	virtual bool IsButtonDown(ButtonCode_t code) const = 0;
	virtual int GetButtonPressedTick(ButtonCode_t code) const = 0;
	virtual int GetButtonReleasedTick(ButtonCode_t code) const = 0;
	virtual int GetAnalogValue(AnalogCode_t code) const = 0;
	virtual int GetAnalogDelta(AnalogCode_t code) const = 0;
	virtual int GetEventCount() const = 0;
	virtual const InputEvent_t* GetEventData() const = 0;
	virtual void PostUserEvent(const InputEvent_t& event) = 0;
	virtual int GetJoystickCount() const = 0;
	virtual void EnableJoystickInput(int nJoystick, bool bEnable) = 0;
	virtual void EnableJoystickDiagonalPOV(int nJoystick, bool bEnable) = 0;
	virtual void SampleDevices(void) = 0;
	virtual void SetRumble(float fLeftMotor, float fRightMotor, int userId = INVALID_USER_ID) = 0;
	virtual void StopRumble(void) = 0;
	virtual void ResetInputState() = 0;
	virtual void SetPrimaryUserId(int userId) = 0;
	virtual const char* ButtonCodeToString(ButtonCode_t code) const = 0;
	virtual const char* AnalogCodeToString(AnalogCode_t code) const = 0;
	virtual ButtonCode_t StringToButtonCode(const char* pString) const = 0;
	virtual AnalogCode_t StringToAnalogCode(const char* pString) const = 0;
	virtual void SleepUntilInput(int nMaxSleepTimeMS = -1) = 0;
	virtual ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey) const = 0;
	virtual int ButtonCodeToVirtualKey(ButtonCode_t code) const = 0;
	virtual ButtonCode_t ScanCodeToButtonCode(int lParam) const = 0;
	virtual int GetPollCount() const = 0;
	virtual void SetCursorPosition(int x, int y) = 0;
	virtual void* GetHapticsInterfaceAddress() const = 0;
	virtual void SetNovintPure(bool bPure) = 0;
	virtual bool GetRawMouseAccumulators(int& accumX, int& accumY) = 0;
	virtual void SetConsoleTextMode(bool bConsoleTextMode) = 0;
	virtual ISteamController* SteamControllerInterface() = 0;
	virtual uint32_t GetNumSteamControllersConnected() = 0;
	virtual bool IsSteamControllerActive() = 0;
	virtual bool IsSteamControllerConnected() = 0;
	virtual int GetSteamControllerIndexForSlot(int nSlot) = 0;
	virtual bool GetRadialMenuStickValues(int nSlot, float& fX, float& fY) = 0;
	virtual void ActivateSteamControllerActionSetForSlot(uint64_t nSlot, GameActionSet_t eActionSet) = 0;
	virtual ControllerActionSetHandle_t GetActionSetHandle(GameActionSet_t eActionSet) = 0;
	virtual ControllerActionSetHandle_t GetActionSetHandle(const char* szActionSet) = 0;
	virtual EControllerActionOrigin GetSteamControllerActionOrigin(const char* action, GameActionSet_t action_set) = 0;
	virtual EControllerActionOrigin GetSteamControllerActionOrigin(const char* action, ControllerActionSetHandle_t action_set_handle) = 0;
	virtual const wchar_t* GetSteamControllerFontCharacterForActionOrigin(EControllerActionOrigin origin) = 0;
	virtual const wchar_t* GetSteamControllerDescriptionForActionOrigin(EControllerActionOrigin origin) = 0;
	virtual void SetSkipControllerInitialization(bool bSkip) = 0;
	//virtual void EnableInput(bool bEnable) = 0;
	void ResetInputStateVFunc()
	{
		typedef void(__thiscall* OrgFn)(void*);
		pVirtualFunc.GetVFunc<OrgFn>(this, 25)(this);
	}
};

class CInput : public IInput
{
public:
	virtual float CAM_CapYaw(float fVal) const { return fVal; }
	virtual float CAM_CapPitch(float fVal) const { return fVal; }

	virtual float JoyStickAdjustYaw(float flSpeed) { return flSpeed; }

	// Public Data
public:
	typedef struct
	{
		unsigned int AxisFlags;
		unsigned int AxisMap;
		unsigned int ControlMap;
	} joy_axis_t;

	enum
	{
		GAME_AXIS_NONE = 0,
		GAME_AXIS_FORWARD,
		GAME_AXIS_PITCH,
		GAME_AXIS_SIDE,
		GAME_AXIS_YAW,
		MAX_GAME_AXES
	};

	enum
	{
		CAM_COMMAND_NONE = 0,
		CAM_COMMAND_TOTHIRDPERSON = 1,
		CAM_COMMAND_TOFIRSTPERSON = 2
	};

	enum
	{
		MOUSE_ACCEL_THRESHHOLD1 = 0,	// if mouse moves > this many mickey's double it
		MOUSE_ACCEL_THRESHHOLD2,		// if mouse moves > this many mickey's double it a second time
		MOUSE_SPEED_FACTOR,				// 0 = disabled, 1 = threshold 1 enabled, 2 = threshold 2 enabled

		NUM_MOUSE_PARAMS,
	};

	class CVerifiedUserCmd
	{
	public:
		CUserCmd	m_cmd;
		unsigned int m_crc;
	};

	inline CUserCmd* m_pCommands() {
		return *reinterpret_cast<CUserCmd**>(reinterpret_cast<DWORD>(this) + 0xFC);
	}

	inline CVerifiedUserCmd* m_pVerifiedCommands() {
		return *reinterpret_cast<CVerifiedUserCmd**>(reinterpret_cast<DWORD>(this) + 0x100);
	}
};