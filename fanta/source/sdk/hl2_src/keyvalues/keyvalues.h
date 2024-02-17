#pragma once
class KeyValues;
class CKeyValueUtils
{
public:
	KeyValues* FindKey(KeyValues* keyValue, const char* keyName, bool bCreate)
	{
		return reinterpret_cast<KeyValues * (__thiscall*)(KeyValues*, const char*, bool)>(pOffsets.m_dwFindKey) (keyValue, keyName, bCreate);
	}
	KeyValues* Initialize(KeyValues* keyValue, char* name)
	{
		return reinterpret_cast<KeyValues * (__thiscall*)(KeyValues*, char*)>(pOffsets.m_dwInitializeKeyValue)(keyValue, name);
	}
}; inline CKeyValueUtils pKeyValueUtils;
class KeyValues
{
public:
	KeyValues(const char* keyName)
	{
		char szName[512];
		sprintf_s(szName, sizeof(szName), keyName);
		pKeyValueUtils.Initialize(this, szName);
	}
	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};

public:
	int m_iKeyName;
	char* m_sValue;
	wchar_t* m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		unsigned char m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	KeyValues* m_pPeer;
	KeyValues* m_pSub;
	KeyValues* m_pChain;

	void SetString(const char* keyName, const char* value);
	void SetInt(const char* keyName, int value)
	{
		KeyValues* dat = pKeyValueUtils.FindKey(this, keyName, true);
		if (dat) { dat->m_iValue = value; dat->m_iDataType = TYPE_INT; }
	}
};
