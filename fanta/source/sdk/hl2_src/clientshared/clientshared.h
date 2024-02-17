#pragma once
class CClientDllSharedAppSystems
{
public:
	virtual int Count() = 0;
	virtual char const* GetDllName(int idx) = 0;
	virtual char const* GetInterfaceName(int idx) = 0;
};
