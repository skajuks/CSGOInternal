#pragma once
#include <d3d9.h>
#include "../Features/Visuals.h"

namespace gui {

	// Menu toggle
	inline bool open = true;

	// Menu Setup
	inline bool setup = false;

	// WINAPI
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };
	inline WNDPROC originalWindowProcess = nullptr;

	// dx
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const char* className) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const char* windowName) noexcept;
	void DestroyWindow() noexcept;

	bool SetupDirectX() noexcept;
	void DestroyDirectX() noexcept;

	void Setup();

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destory() noexcept;

	void Render() noexcept;

}