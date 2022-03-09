#define WIN32_LEAN_AND_MEAN
#define DEBUG_OUT 1
#define MESSAGE(message) \
MessageBoxA(NULL, message, "CSGOInternal error", MB_OK | MB_ICONERROR)

#include <Windows.h>

#include <thread>
#include <cstdint>
#include <iostream>
#include "Hooks/Hooks.h"

void Setup(LPVOID instance) {
#ifdef DEBUG_OUT
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
#endif

	while (!GetModuleHandle("serverbrowser"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	// try to init all core cheat functions
	try {

		signatures::Setup();
		DEBUG("Signatures Setup()");
		interfaces::Setup();
		DEBUG("Interfaces Setup()");
		SetupNetvars();
		DEBUG("Netvars Setup()");
		gui::Setup();
		DEBUG("Gui Setup()");
		hooks::Setup();
		DEBUG("Hooks Setup()");
		globals::entities.Setup();
		DEBUG("Entity Setup()");

	}
	catch (const std::exception& error) {
#ifdef DEBUG_OUT
		if (file)
			fclose(file);
		FreeConsole();
#endif

		hooks::Destroy();
		gui::Destory();
		globals::entities.Destroy();
		globals::Destory();
		MESSAGE(error.what());
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), EXIT_SUCCESS);
	}

	while (!GetAsyncKeyState(VK_END)) {

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

#ifdef DEBUG_OUT
	if(file)
		fclose(file);
	FreeConsole();
#endif

	hooks::Destroy();
	gui::Destory();
	globals::entities.Destroy();
	globals::Destory();
	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), EXIT_SUCCESS);

}

BOOL WINAPI DllMain(const HMODULE instance, const std::uintptr_t reason, const void* reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(instance);

		const HANDLE thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
			instance,
			0,
			nullptr
		);

		if (thread)
			CloseHandle(instance);
	}

	return TRUE;

}