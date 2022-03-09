#pragma once
#include <cstdint>
#include <vector>
#include <Windows.h>

struct sigs {
    uint8_t* glowObjectManager;
    uint8_t* allocKeyValuesEngine = nullptr;
    uint8_t* allocKeyValuesClient = nullptr;
};

namespace signatures {

    void Setup();

    inline sigs s_signatures;

    std::vector<int> PatternToBytes(const char* pattern);

    uint8_t* Scan(const char* module, const char* pattern);

}
