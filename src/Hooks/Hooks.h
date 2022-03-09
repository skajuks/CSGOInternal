#pragma once
#include "../Interfaces/Interfaces.h"
#include "../Gui/Gui.h"

namespace hooks {

	void Setup();
	void Destroy() noexcept;

	using CreateMoveFn = bool(__thiscall*)(void*, float, UserCmd*) noexcept;
	static CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, UserCmd* cmd) noexcept;

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetFnOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;

	using AllocKeyValuesFn = void* (__thiscall*)(void*, int);
	inline AllocKeyValuesFn AllocKeyValuesOriginal = nullptr;
	void* __stdcall AllocKeyValues(int size);

	//using FrameStageNotifyFn = void(__thiscall*)(void*, ClientFrameStage);
	//inline FrameStageNotifyFn FrameStageNotifyOriginal = nullptr;
	//void __stdcall FrameStageNotify(ClientFrameStage stage);

	using DoPostScreenSpaceEffectsFn = int(__thiscall*)(void*, const ViewSetup*) noexcept;
	inline DoPostScreenSpaceEffectsFn DoPostScreenSpaceEffectsOriginal = nullptr;
	int __stdcall DoPostScreenSpaceEffects(const ViewSetup* view) noexcept;

	//using PaintTraverseFn = void(__thiscall*)(void*, unsigned int, bool, bool);
	//inline PaintTraverseFn PaintTraverseOriginal = { nullptr };
	//void __stdcall PaintTraverse(VPANEL panel, bool forceRepaint, bool allowForce);

	using LevelInitPreEntityFn = void(__thiscall*)(void*, const char*) noexcept;
	inline LevelInitPreEntityFn LevelInitPreEntityOriginal = nullptr;
	void __stdcall LevelInitPreEntity(const char* map) noexcept;

	using DrawModelFn = void(__thiscall*)(void*, void*, const DrawModelInfo&, CMatrix3x4*, float*, float*, const CVector&, const int32_t) noexcept;
	inline DrawModelFn DrawModelFnOriginal = nullptr;
	void __stdcall DrawModel(void* results, const DrawModelInfo& info, CMatrix3x4* bones, float* weights, float* delayedWeights, const CVector& modelOrigin, const int32_t flags) noexcept;
}