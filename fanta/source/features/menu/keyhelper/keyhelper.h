#pragma once
#include<Windows.h>

class KeyHelper
{
private:
	enum class KeyState{None, Down};
	int* Key = nullptr;
	KeyState LastState = KeyState::None;
public:
	explicit KeyHelper(int* vkey) { Key = vkey; }
	bool Down()
	{
		if (!*Key) { LastState = KeyState::None; return false; }
		const bool isDown = GetAsyncKeyState(*Key) & 0x8000;
		LastState = isDown ? KeyState::Down : KeyState::None;
		return isDown;
	}
	bool Pressed() 
	{ 
		const bool check = LastState == KeyState::None;
		return Down() && check;
	}

	bool Release()
	{
		const bool check = LastState == KeyState::Down;
		return !Down() && check;
	}
};
