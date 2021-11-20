#pragma once

#include <vector>
#include "Hook.h"

class HookManager
{
    static inline std::vector<Hook *> *hooks = new std::vector<Hook *>();

public:
    static void InitHooks();
    static void AddHook(Hook *hook);
    static void RemoveHooks();
    static void RemoveHook(Hook *hook);
};
