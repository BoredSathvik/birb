#include "hook_manager.h"

HookManager::HookManager()
{
    MH_Initialize();
    hooks = new std::vector<Hook *>();

    hooks->push_back(new KeyHook());
    hooks->push_back(new MouseHook());
}

HookManager::~HookManager()
{
}

void HookManager::HookAll()
{
    for (auto hook : *hooks)
    {
        hook->HookFunc();
    }
}

void HookManager::CleanHooks()
{
    for (auto hook : *hooks)
    {
        delete hook;
    }
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    hooks->clear();
    delete hooks;
}

template <typename T> T *HookManager::GetHook(char *name)
{
    for (auto hook : *hooks)
    {
        if (hook->name == std::string(name))
        {
            return (T *)hook;
        }
    };
}
