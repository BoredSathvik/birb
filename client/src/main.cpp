
#include "gui/gui.h"
#include "utils/global.h"
#include "hook/hook_manager.h"

#pragma comment(lib, "windowsapp")
#pragma comment(lib, "dxguid.lib")

using namespace winrt::Windows::ApplicationModel::Core;

static inline uintptr_t func_original = 0;

// void KeyHook(int key, int state)
// {
//     auto io = ImGui::GetIO();

//     Logger::LogF("Key pressed");

//     return PLH::FnCast(func_original, KeyHook)(key, state);
// }

void start(HMODULE h_mod)
{
    Logger::LogF("Starting...");

    Gui::GetInstance()->Init();

    // PLH::CapstoneDisassembler dis = PLH::CapstoneDisassembler(PLH::Mode::x64);

    // uintptr_t hook_addr = Mem::AOBScan("48 ?? ?? ?? 0F B6 ?? 4C ?? ?? ?? ?? ?? ?? 89 ?? ?? ?? 88");

    // if (hook_addr == 0)
    // {
    //     Logger::LogF("Failed to find hook address");
    // }
    // else
    // {
    //     auto detour = new PLH::x64Detour((char *)hook_addr, (char *)KeyHook, (uint64_t *)&func_original, dis);

    //     detour->hook();
    // }
    HookManager::GetInstance()->HookAll();
}

BOOL __stdcall DllMain(HMODULE h_mod, int reason, void *)
{
    if (reason == 1)
    {
        Global::h_mod = h_mod;

        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)start, h_mod, 0, nullptr));
    }
    else if (reason == 0)
    {
    }
    return true;
}
