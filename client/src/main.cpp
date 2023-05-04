
#include "gui/gui.h"
#include "hook/hook_manager.h"
#include "module/module_manager.h"
#include "utils/global.h"

#pragma comment(lib, "windowsapp")
#pragma comment(lib, "dxguid.lib")

DWORD WINAPI start()
{
    Logger::LogF("Starting...");

    HookManager::GetInstance()->HookAll();
    Gui::GetInstance()->Init();
    ModuleManager::GetInstance()->Init();

    // Runs every vsync
    while (true)
    {
        if (!Gui::GetInstance()->dx_manager->resizing)
        {
            if (!Global::running)
            {
                break;
            }

            Gui::GetInstance()->Render();

            Gui::GetInstance()->dx_manager->swapchain->Present(1, 0);
        }
        else
        {
            Sleep(50);
        }
    }

    HookManager::GetInstance()->CleanHooks();
    ModuleManager::GetInstance()->CleanModules();
    Gui::GetInstance()->CleanGui();

    Logger::LogF("Freeing Library...");

    Sleep(100);
    FreeLibraryAndExitThread(Global::h_mod, 0);

    return 0;
}

BOOL __stdcall DllMain(HMODULE h_mod, int reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        Global::h_mod = h_mod;
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start,
                                 NULL, 0, NULL));

    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return true;
}
