#pragma once
#include "Entity.h"
#include "../Structs/ClientClass.h"
#include "../Structs/CUserCmd.h"
#include "../Structs/IEngineClient.h"
#include "../Structs/IEngineTraceClient.h"
#include "../Structs/IClientEntityList.h"
#include "../Structs/GlowObjectManager.h"
#include "../Structs/ViewSetup.h"
#include "../Structs/InterfaceReg.h"
#include "../Structs/MaterialSystem.h"
#include "../Structs/IStudioRender.h"
#include "Globals.h"
#include "Definitions.h"
#include "../Offsets/Signatures/Signatures.h"
#define DEBUG(message) \
std::cout << message << '\n'

namespace interfaces {
	
	// call once to setup
	void Setup();

	/*template <typename T>
	T* GetInterface(const char* name, const char* library) noexcept;*/
	template <typename T>
	T* Get(const char* module, const std::string_view& ver) noexcept;

	inline IClientEntityList* entityList = nullptr;
	inline IEngineClient* engine = nullptr;
	inline IEngineTraceClient* trace = nullptr;
	inline IClient* client = nullptr;
	inline GlowObjectManager* glow = nullptr;
	inline KeyValues* keyValues = nullptr;
	inline MaterialSystem* materialSys = nullptr;
	inline IStudioRender* render = nullptr;
	//inline Panel* panel = nullptr;

	inline void* clientMode = nullptr;
};

enum ClientFrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,
	FRAME_RENDER_END,

	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};