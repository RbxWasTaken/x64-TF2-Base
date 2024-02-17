#pragma once
#include<unordered_map>
#include<unordered_set>
#include <memory>
#include <string>
#include"../../sdk/interfaces/interfaces.h"

inline int GetOffset(RecvTable* pTable, const char* szNetVar)
{
	for (int index = 0; index < pTable->m_nProps; index++)
	{
		RecvProp Prop = pTable->m_pProps[index];

		if (std::string_view(Prop.m_pVarName).compare(szNetVar) == 0)
			return Prop.GetOffset();

		if (auto DataTable = Prop.GetDataTable())
		{
			if (auto nOffset = GetOffset(DataTable, szNetVar))
				return nOffset = Prop.GetOffset();
		}
	}
	return 0;
}

inline int GetNetVar(const char* szClass, const char* szNetVar)
{
	CClientClass* pClasses = pHl2Interfaces.BaseClientDll->GetAllClasses();
	for (auto pCurrNode = pClasses; pCurrNode; pCurrNode = pCurrNode->pNext)
	{
		if (std::string_view(szClass).compare(pCurrNode->pNetworkName) == 0)
			return GetOffset(pCurrNode->pRecvTable, szNetVar);
	}
}

class CNetVars
{
	struct node;
	using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

	struct node
	{
		node(DWORD offset) : offset(offset) {}
		map_type nodes;
		DWORD offset;
	};

	map_type nodes;

public:
	void Initialize()
	{
		const auto* client_class = pHl2Interfaces.BaseClientDll->GetAllClasses();
		while (client_class != nullptr)
		{
			const auto class_info = std::make_shared<node>(0);
			RecvTable* recv_table = reinterpret_cast<RecvTable*>(client_class->pRecvTable);
			if (!class_info || !recv_table)
				continue;

			populate_nodes(recv_table, &class_info->nodes);
			nodes.emplace(recv_table->GetName(), class_info);

			client_class = client_class->pNext;

		}
	}

private:
	void populate_nodes(class RecvTable* recv_table, map_type* map)
	{
		for (auto i = 0; i < recv_table->GetNumProps(); i++)
		{
			const auto* prop = recv_table->GetPropW(i);
			const auto prop_info = std::make_shared<node>(prop->GetOffset());

			if (prop->GetType() == DPT_DataTable)
				populate_nodes(prop->GetDataTable(), &prop_info->nodes);

			map->emplace(prop->GetName(), prop_info);
		}
	}

	DWORD get_offset_recursive(map_type& map, int acc, const char* name)
	{
		return acc + map[name]->offset;
	}

	template<typename ...args_t>
	DWORD get_offset_recursive(map_type& map, int acc, const char* name, args_t ...args)
	{
		const auto& node = map[name];
		return get_offset_recursive(node->nodes, acc + node->offset, args...);
	}

public:
	template<typename ...args_t>
	DWORD get_offset(const char* name, args_t ...args)
	{
		const auto& node = nodes[name];
		return get_offset_recursive(node->nodes, node->offset, args...);
	}
}; 
inline CNetVars pNetVars;

template<typename Type>
class CDynamicNetvar {
private:
	DWORD dwOffset;
public:
	template<typename... args_t>
	CDynamicNetvar(args_t... a) { dwOffset = pNetVars.get_offset(a...); }
	template<typename... args_t>
	CDynamicNetvar(int nOffset, args_t... a) { dwOffset = pNetVars.get_offset(a...) + nOffset; }
public:
	Type GetValue(void* ptr) { return *reinterpret_cast<Type*>(reinterpret_cast<DWORD>(ptr) + dwOffset); }
	void SetValue(void* ptr, Type val) { reinterpret_cast<Type*>(reinterpret_cast<DWORD>(ptr) + dwOffset) = val; }
}; 

#define DYNVAR(name, type, ...) static CDynamicNetvar<type> name(__VA_ARGS__)
#define DYNVAR_RETURN(type, base, ...) DYNVAR(n, type, __VA_ARGS__); return n.GetValue(base)
#define DYNVAR_SET(type, base, value, ...) DYNVAR(n, type, __VA_ARGS__); n.SetValue(base,value)

#define M_DYNVARGET(name, type, base, ...) __inline type Get##name() \
{ \
	static CDynamicNetvar<type>  Var##name( __VA_ARGS__ ); \
	return Var##name.GetValue(base); \
}

#define NETVAR(_name, type, table, name) inline type &_name() \
{ \
	static const int nOff = GetNetVar(table, name); \
	return *reinterpret_cast<type*>(reinterpret_cast<unsigned long>(this) + nOff); \
}
