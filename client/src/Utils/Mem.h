#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <vector>

class Mem
{
public:
    static uintptr_t AOBScan(const char *pattern);
    static uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
    static HMODULE GetThisModule();
};
