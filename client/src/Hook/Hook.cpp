#include "Hook.h"

Hook::Hook(std::string name, std::string sig)
{
    this->name = name;
    this->signature = sig;
}

Hook::~Hook()
{
    this->detour->unHook();
    delete this->detour;
}

bool Hook::run()
{
    return false;
}

bool Hook::hookFn(void *fnCB, uintptr_t *fnOG)
{
    uintptr_t pos = Mem::AOBScan(this->signature.c_str());

    if (!pos)
    {
        Utils::DebugF(std::string("ERROR: Pattern for " + this->name + " failed").c_str());
        return false;
    }

    PLH::CapstoneDisassembler dis = PLH::CapstoneDisassembler(PLH::Mode::x64);
    this->detour = new PLH::x64Detour((uint64_t)pos, (uint64_t)fnCB, (uint64_t *)fnOG, dis);

    if (!this->detour->hook())
    {
        Utils::DebugF(std::string("ERROR: " + this->name + " hook failed").c_str());
        return false;
    }

    return true;
}
