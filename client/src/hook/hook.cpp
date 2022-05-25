#include "hook.h"

Hook::Hook(std::string name, std::string signature)
{
    this->name = name;
    this->signature = signature;
}

Hook::~Hook()
{
    this->detour->unHook();
    delete this->detour;
}

void Hook::HookFunc()
{
}

bool Hook::AutoHook(void *callback_ptr, uintptr_t *func_original)
{

    PLH::CapstoneDisassembler dis = PLH::CapstoneDisassembler(PLH::Mode::x64);

    uintptr_t hook_addr = Mem::AOBScan(this->signature.c_str());

    Logger::LogF(std::string("Hook addr: ").append(std::to_string(hook_addr)));

    if (hook_addr == 0)
    {
        Logger::LogF(std::string("[Hook] Failed to find address of ").append(this->name));
        return false;
    }

    this->detour = new PLH::x64Detour((char *)hook_addr, (char *)callback_ptr, (uint64_t *)func_original, dis);

    if (!detour->hook())
    {
        Logger::LogF(std::string("[Hook] Failed to hook ").append(this->name));
        return false;
    }

    return true;
}