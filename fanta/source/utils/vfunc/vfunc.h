#pragma once
#include<cstdint>
class VirtualFunc
{
public:
	__inline void**& GetVTable(void* ptr, size_t offset = 0) {
		return *reinterpret_cast<void***>(reinterpret_cast<size_t>(ptr) + offset);
	}
	__inline const void** GetVTable(const void* ptr, size_t offset = 0) {
		return *reinterpret_cast<const void***>(reinterpret_cast<size_t>(ptr) + offset);
	}
public:
	template<typename type>
	__inline type GetVFunc(const void* ptr, size_t index, size_t offset = 0) {
		return reinterpret_cast<type>(GetVTable(ptr, offset)[index]);
	}
public:
	__inline uintptr_t GetVFuncPtr(void* ptr, unsigned int index) {
		return static_cast<uintptr_t>((*static_cast<int**>(ptr))[index]);
	}
}; VirtualFunc pVirtualFunc;