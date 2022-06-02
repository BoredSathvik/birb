#pragma once

#include <vector>
#include "hook.h"
#include "hooks/key_hook.h"
#include "hooks/mouse_hook.h"

class HookManager
{
private:
    HookManager();
    ~HookManager();

public:
    std::vector<Hook *> *hooks;

    static HookManager *GetInstance()
    {
        static HookManager instance;
        return &instance;
    };

    void HookAll();
    void CleanHooks();

    template <typename T>
    T *GetHook(char *name);
};