#include "Signatures.h"

void signatures::Setup() {

    s_signatures.glowObjectManager = Scan("client", "0F 11 05 ? ? ? ? 83 C8 01") + 3;
    s_signatures.allocKeyValuesClient = Scan("client", "FF 52 04 85 C0 74 0C 56") + 3;
    s_signatures.allocKeyValuesEngine = Scan("engine", "FF 52 04 85 C0 74 0C 56") + 3;
}

std::vector<int> signatures::PatternToBytes(const char* pattern) {
    auto bytes = std::vector<int>{};
    auto start = const_cast<char*>(pattern);
    auto end = const_cast<char*>(pattern) + std::strlen(pattern);

    for (auto current = start; current < end; current++) {
        if (*current == '?') {
            current++;

            if (*current == '?')
                current++;

            bytes.push_back(-1);
        }
        else {
            bytes.push_back(std::strtoul(current, &current, 16));
        }
    }
    return bytes;
}

uint8_t* signatures::Scan(const char* module, const char* pattern) {
    const auto handle = GetModuleHandle(module);

    if (!handle)
        return nullptr;

    auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
    auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(handle) + dosHeader->e_lfanew);
    auto size = ntHeaders->OptionalHeader.SizeOfImage;
    auto bytes = PatternToBytes(pattern);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(handle);

    auto s = bytes.size();
    auto d = bytes.data();

    for (auto i = 0ul; i < size - s; ++i) {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {

                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }
}