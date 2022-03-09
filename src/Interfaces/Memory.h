#pragma once
#include <cstdint>
#include <Windows.h>

namespace memory {

	template <typename Return, typename ... Args>
	constexpr Return Call(void* _this, const uintptr_t index, Args ... args) noexcept {

		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(_this))[index](_this, args...);
	}

	constexpr void* Get(void* voidptr, const uintptr_t index) noexcept {
		return (*static_cast<void***>(voidptr))[index];
	}

	template<typename T = uintptr_t>
	constexpr T RelToAbs(const uintptr_t addr) noexcept {
		return static_cast<T>(addr + 4 + *reinterpret_cast<uint32_t*>(addr));
	}

}