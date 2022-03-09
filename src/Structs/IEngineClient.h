#pragma once
#include <cstdint>
#include "../Interfaces/Memory.h"
#include "../Math/CVector.h"
#include "CUserCmd.h"

class IEngineClient {
public:
    //constexpr bool GetPlayerInfo(int id, const PlayerInfo& playerInfo) noexcept {
        //return memory::Call<bool, const PlayerInfo&>(this, 8, playerInfo);
    //}

    constexpr int32_t GetLocalPlayerIndex() noexcept {
        return memory::Call<int32_t>(this, 12);
    }

    constexpr void GetViewAngles(const CVector& viewAngles) noexcept {
        return memory::Call<void, const CVector&>(this, 18, viewAngles);
    }

    constexpr void SetViewAngles(const CVector& viewAngles) noexcept {
        memory::Call<void, const CVector&>(this, 19, viewAngles);
    }

    constexpr int32_t GetMaxClients() noexcept {
        return memory::Call<int32_t>(this, 20);
    }

    constexpr bool IsInGame() noexcept {
        return memory::Call<bool>(this, 26);
    }

    constexpr const char* GetLevelName() noexcept {
        return memory::Call<const char*>(this, 52);
    }
};



struct Matrix4x4 {
    union {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;

        };
        float m[4][4];
    };
};

struct PlayerInfo {
    std::uint64_t version;
    union {
        std::uint64_t xuid;
        struct {
            std::uint32_t xuidLow;
            std::uint32_t xuidHigh;
        };
    };
    char name[128];
    int userId;
    char guid[33];
    std::uint32_t friendsId;
    char friendsName[128];
    bool fakeplayer;
    bool hltv;
    int customfiles[4];
    unsigned char filesDownloaded;
};
