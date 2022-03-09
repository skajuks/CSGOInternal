#include "Interfaces.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdexcept>

void interfaces::Setup() {

	DEBUG("Starting interface setup()");
	if (!(trace = Get<IEngineTraceClient>("engine", "EngineTraceClient")))
		throw std::runtime_error("Failed to get entityList interface from client.dll");
	DEBUG("Interface trace setup sucessfully");
	if (!(client = Get<IClient>("client", "VClient")))
		throw std::runtime_error("Failed to get client interface from client.dll");
	DEBUG("Interface client setup sucessfully");
	if (!(entityList = Get<IClientEntityList>("client", "VClientEntityList")))
		throw std::runtime_error("Failed to get entityList interface from client.dll");
	DEBUG("Interface entityList setup sucessfully");
	if (!(engine = Get<IEngineClient>("engine", "VEngineClient")))
		throw std::runtime_error("Failed to get entityList interface from client.dll");
	DEBUG("Interface engine setup sucessfully");

	keyValues = reinterpret_cast<KeyValuesSystemFn>(GetProcAddress(GetModuleHandle("vstdlib"), "KeyValuesSystem"))();
	if (!keyValues)
		throw std::runtime_error("Failed to get keyValuesSystem ptr");
	DEBUG("Interface KeyValues setup sucessfully");

	glow = *reinterpret_cast<GlowObjectManager**>(signatures::s_signatures.glowObjectManager);
	DEBUG("Interface Glow setup sucessfully");

	if (!(materialSys = Get<MaterialSystem>("materialsystem", "VMaterialSystem")))
		throw std::runtime_error("Failed to get MaterialSystem, interface from materialsystem");
	DEBUG("Interface MaterialSystem setup sucessfully");

	if (!(render = Get<IStudioRender>("studiorender", "VStudioRender")))
		throw std::runtime_error("Failed to get IStudioRender, interface from VStudioRender");
	DEBUG("Interface IStudioRender setup sucessfully");

	clientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	DEBUG("Interface Clientmode setup sucessfully");
}

/*template <typename T>
T* interfaces::GetInterface(const char* name, const char* library) noexcept {

	const HINSTANCE handle = GetModuleHandle(library);

	if (!handle)
		return nullptr; //better error handle pls

	using Fn = T * (*)(const char*, int*);
	const Fn CreateInterface = reinterpret_cast<Fn>(GetProcAddress(handle, "CreateInterface"));

	return CreateInterface(name, nullptr);
}*/

template <typename T>
T* interfaces::Get(const char* module, const std::string_view& ver) noexcept {

	const auto handle = GetModuleHandleA(module);

	if (!handle)
		return nullptr; //better error handle pls
	
	const auto createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));

	if (!createInterface)
		return nullptr;

	const auto rel = createInterface + 5;
	const auto addr = memory::RelToAbs(rel);
	const auto interfaces = **reinterpret_cast<InterfaceReg***>(addr + 6);

	if (!interfaces)
		return nullptr;

	for (auto item = interfaces; item; item = item->next) {
		if ((!std::string_view(item->name).compare(0U, ver.length(), ver) && std::atoi(item->name + ver.length()) > 0) || !ver.compare(item->name)) {

			DEBUG(item->name);
			const auto ptr = item->CreateInterface();

			if (!ptr)
				return nullptr;

			return static_cast<T*>(ptr);
		}
	}
	return nullptr;
}