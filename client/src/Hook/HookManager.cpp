#include "HookManager.h"
#include "Hooks/UIRenderer.h"
#include "Hooks/Keyboard.h"

void HookManager::InitHooks()
{
    HookManager::AddHook(new UIRenderer());
    HookManager::AddHook(new Keyboard());
}

void HookManager::AddHook(Hook *hook)
{
    if (hook->run())
    {
        Utils::DebugF(std::string("Successfully hooked " + hook->name));
        HookManager::hooks->push_back(hook);
    }
}

void HookManager::RemoveHooks()
{
    for (auto hook : *HookManager::hooks)
    {
        HookManager::RemoveHook(hook);
    }
    HookManager::hooks->clear();
    delete HookManager::hooks;
}

void HookManager::RemoveHook(Hook *hook)
{
    delete hook;
}