#pragma once

#include <vector>
#include "Hook.h"

class HookManager
{
    static inline std::vector<class Hook *> *hooks = new std::vector<class Hook *>();

public:
    static void InitHooks();
    static void AddHook(Hook *hook);
    static void RemoveHooks();
    static void RemoveHook(Hook *hook);
};
