#pragma once
#include"winapi.h"
typedef struct SysMem
{
	DWORD64 dwEP;
	LPVOID dwParam;
}SysMem, * pSysMem;
typedef DWORD(*InitMem)(LPVOID Param);
void InitThread(SysMem* mMemory)
{
	if (mMemory != NULL && mMemory->dwEP != NULL)
	{
		InitMem CallMem = (InitMem)mMemory->dwEP;
		CallMem(mMemory->dwParam);
	}
}
