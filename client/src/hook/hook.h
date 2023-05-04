#pragma once

#include "MinHook.h"
#include <string>

#include "../utils/logger.h"
#include "../utils/mem.h"

class Hook
{
  public:
    std::string signature;
    std::string name;

    Hook(std::string name, std::string signature);
    virtual ~Hook();

    virtual void HookFunc();

    bool AutoHook(void *callback_ptr, void **func_original);
    bool ManualHook(void *hook_addr, void *callback_ptr, void **func_original);
};