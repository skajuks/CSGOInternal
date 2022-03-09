#pragma once
#include "../../Hash/fnv.h"
#include "../../Structs/ClientClass.h"
#include <unordered_map>

// Call once to dump netvars
void SetupNetvars() noexcept;

// Recursive dump
void Dump(const char* baseClass, RecvTable* table, std::uint32_t offset = 0);

// Hold the offsets
inline std::unordered_map<std::uint32_t, std::uint32_t> netvars;

#define NETVAR(func_name, netvar, type) type& func_name() \
{ \
	static auto offset = netvars[fnv::HashConst(netvar)]; \
	return *reinterpret_cast<type*>(std::uint32_t(this) + offset); \
}


