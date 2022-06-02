
#include "gui/gui.h"
#include "utils/global.h"
#include "hook/hook_manager.h"

#pragma comment(lib, "windowsapp")
#pragma comment(lib, "dxguid.lib")

using namespace winrt::Windows::ApplicationModel::Core;

void start(HMODULE h_mod)
{
    Logger::LogF("Starting...");

    Gui::GetInstance()->Init();
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
