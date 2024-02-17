#pragma once
#include"visuals/visuals.h"

class CFeatures
{
public:
	__inline void Initialize()
	{
		static bool m_bInit = false;
		while (!m_bInit)
		{
		}
	}
}; CFeatures pFeatures;