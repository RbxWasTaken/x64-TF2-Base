#pragma once
class CUniformRandomStream 
{
public:
	virtual void SetSeed(int iSeed) = 0;
	virtual float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f) = 0;
	virtual int RandomInt(int nMinVal, int nMaxval) = 0;
	virtual float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExp = 1.0f) = 0;
};