#pragma once

#include <vector>
#include "hook.h"
#include "hooks/key_hook.h"
#include "hooks/mouse_hook.h"

class HookManager
{
private:
    std::vector<Hook *> *hooks;

    HookManager();
    ~HookManager();

public:
    static HookManager *GetInstance()
    {
        static HookManager *instance = new HookManager();
        return instance;
    };

    void HookAll();

    template <typename T>
    T *GetHook(char *name);
};