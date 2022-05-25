#pragma once

#include <string>
#include <polyhook2/Detour/x64Detour.hpp>
#include <polyhook2/CapstoneDisassembler.hpp>

#include "../utils/mem.h"
#include "../utils/logger.h"

class Hook
{
public:
    std::string signature;
    std::string name;

    PLH::x64Detour *detour;

    Hook(std::string name, std::string signature);
    virtual ~Hook();

    virtual void HookFunc();

    bool AutoHook(void *callback_ptr, uintptr_t *func_original);
};