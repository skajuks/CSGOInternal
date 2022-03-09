#include "Hooks.h"
#include "../../deps/minhook/minhook.h"
#include "../../deps/imgui/imgui.h"
#include "../../deps/imgui/imgui_impl_win32.h"
#include "../../deps/imgui/imgui_impl_dx9.h"
#include <stdexcept>
#include <intrin.h>
#include "../Features/Visuals.h"
#include "../Features/Misc.h"

void hooks::Setup() {

	// get entity list if in game
	globals::Setup();

	DEBUG("Calling hooks Setup()");

	if (MH_Initialize())
		throw std::runtime_error("Failed to initialize MinHook");
	DEBUG("MH_Initialize() call successful");

	// Must be ran as first hook to bypass return address for other modules
	if (MH_CreateHook(memory::Get(interfaces::keyValues, 1), &AllocKeyValues, reinterpret_cast<void**>(&AllocKeyValuesOriginal)))
		throw std::runtime_error("Failed to hook AllocKeyValues");
	DEBUG("AllocKeyValues hook setup successfuly");

	if (MH_CreateHook(memory::Get(interfaces::clientMode, 24), &CreateMove, reinterpret_cast<void**>(&CreateMoveOriginal)))
		throw std::runtime_error("Failed to hook CreateMove");
	DEBUG("CreateMove hook setup successfuly");

	if (MH_CreateHook(memory::Get(gui::device, 42), &EndScene, reinterpret_cast<void**>(&EndSceneOriginal)))
		throw std::runtime_error("Failed to hook EndScene");
	DEBUG("EndScene hook setup successfuly");

	if (MH_CreateHook(memory::Get(gui::device, 16), &Reset, reinterpret_cast<void**>(&ResetFnOriginal)))
		throw std::runtime_error("Failed to hook Reset");
	DEBUG("Reset hook setup successfuly");

	if (MH_CreateHook(memory::Get(interfaces::clientMode, 44), &DoPostScreenSpaceEffects, reinterpret_cast<void**>(&DoPostScreenSpaceEffectsOriginal)))
		throw std::runtime_error("Failed to hook DoPostScreenSpaceEffects");
	DEBUG("DoPostScreenSpaceEffects hook setup successfuly");

	if (MH_CreateHook(memory::Get(interfaces::client, 5), &LevelInitPreEntity, reinterpret_cast<void**>(&LevelInitPreEntityOriginal)))
		throw std::runtime_error("Failed to hook LevelInitPreEntity");
	DEBUG("LevelInitPreEntity hook setup successfuly");

	if (MH_CreateHook(memory::Get(interfaces::render, 29), &DrawModel, reinterpret_cast<void**>(&DrawModelFnOriginal)))
		throw std::runtime_error("Failed to hook DrawModel");
	DEBUG("DrawModel hook setup successfuly");

	MH_EnableHook(MH_ALL_HOOKS);
	gui::DestroyDirectX();
}

void hooks::Destroy() noexcept {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

bool __stdcall hooks::CreateMove(float frameTime, UserCmd* cmd) noexcept {

	const bool result = CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);

	if (!cmd->commandNumber)
		return result;

	if (result)
		interfaces::engine->SetViewAngles(cmd->viewPoint);

	globals::localPlayer = static_cast<CSPlayer*>(interfaces::entityList->GetEntityFromIndex(interfaces::engine->GetLocalPlayerIndex()));

	if (!globals::localPlayer || !globals::localPlayer->IsAlive())
		return false;

	misc::BunnyHop(cmd);
	misc::RevealPlayerRanks(cmd);

	return false;
};

long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept {

	static const auto returnAddress = _ReturnAddress();
	const auto result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == returnAddress)
		return result;

	if (!gui::setup)
		gui::SetupMenu(device);

	if (gui::open)
		gui::Render();

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept {

	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetFnOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}

void* __stdcall hooks::AllocKeyValues(int size) {

	static const auto allocEngine = reinterpret_cast<uintptr_t>(signatures::s_signatures.allocKeyValuesEngine);
	static const auto allocClient = reinterpret_cast<uintptr_t>(signatures::s_signatures.allocKeyValuesClient);

	if (const auto retAddr = reinterpret_cast<uintptr_t>(_ReturnAddress()); retAddr == allocEngine || retAddr == allocClient)
		return nullptr;
	return AllocKeyValuesOriginal(interfaces::keyValues, size);	
}

int __stdcall hooks::DoPostScreenSpaceEffects(const ViewSetup* view) noexcept {
	visuals::Glow();
	return DoPostScreenSpaceEffectsOriginal(interfaces::clientMode, view);
}

void __stdcall hooks::LevelInitPreEntity(const char* map) noexcept {
	visuals::ChangeWorldColors();
	LevelInitPreEntityOriginal(interfaces::client, map);
}

void __stdcall hooks::DrawModel(void* results, const DrawModelInfo& info, CMatrix3x4* bones, float* weights,
	float* delayedWeights, const CVector& modelOrigin, const int32_t flags) noexcept {

	if (interfaces::render->IsForcedMaterialOverride())
		return DrawModelFnOriginal(interfaces::render, results, info, bones, weights, delayedWeights, modelOrigin, flags);

	if (globals::localPlayer && info.renderable) {
		if(visuals::ChangeChamsColors(results, info, bones, weights, delayedWeights, modelOrigin, flags))
			return interfaces::render->ForcedMaterialOverride(nullptr);
	}
	DrawModelFnOriginal(interfaces::render, results, info, bones, weights, delayedWeights, modelOrigin, flags);
}