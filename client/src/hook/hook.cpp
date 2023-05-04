#include "hook.h"

Hook::Hook(std::string name, std::string signature)
{
    this->name = name;
    this->signature = signature;
}

Hook::~Hook()
{
}

void Hook::HookFunc()
{
}

bool Hook::AutoHook(void *callback_ptr, void **func_original)
{

    uintptr_t hook_addr = Mem::AOBScan(this->signature.c_str());

    Logger::LogF(std::string("Hook addr: ").append(std::to_string(hook_addr)));

    if (hook_addr == 0)
    {
        Logger::LogF(std::string("[Hook] Failed to find address of ").append(this->name));
        return false;
    }

    MH_CreateHook((void *)hook_addr, callback_ptr, func_original);

    if (MH_EnableHook((void *)hook_addr) != 0)
    {
        Logger::LogF(std::string("[Hook] Failed to hook ").append(this->name));
        return false;
    }

    return true;
}

bool Hook::ManualHook(void *hook_addr, void *callback_ptr, void **func_original)
{
    Logger::LogF(std::string("Hook addr: ").append(std::to_string((uintptr_t)hook_addr)));

    if (hook_addr == 0)
    {
        Logger::LogF(std::string("[Hook] Failed to find address of ").append(this->name));
        return false;
    }

    MH_CreateHook(hook_addr, callback_ptr, func_original);

    if (MH_EnableHook((void *)hook_addr) != 0)
    {
        Logger::LogF(std::string("[Hook] Failed to hook ").append(this->name));
        return false;
    }

    return true;
}