#pragma once

#include <polyhook2/Detour/x64Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>

#include <string>

#include "../Utils/Mem.h"
#include "../Utils/Utils.h"

class Hook
{
    PLH::x64Detour *detour;

public:
    std::string name;
    std::string signature;

    Hook(std::string name, std::string sig);
    virtual ~Hook();
    virtual bool run();
    virtual bool hookFn(void *fnCB, uintptr_t *fnOG);
};
