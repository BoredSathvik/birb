#include <Windows.h>
#include <thread>
#include <chrono>
#include <ctime>

#include "Hook/HookManager.h"
#include "Module/ModuleManager.h"
#include "Utils/Utils.h"

void start()
{

    Utils::DebugF("Seting up modules (1/2)");
    ModuleManager::InitModules();
    Utils::DebugF("Seting up modules (2/2)");
    HookManager::InitHooks();
}

BOOL __stdcall DllMain(HMODULE hModule, int reason, void *)
{
    if (reason == 1)
    {
        Utils::hMod = hModule;
        time_t now = time(0);
        Utils::DebugF("--------------------------------------------------");
        Utils::DebugF(std::string(ctime(&now)).c_str());

        Utils::DebugF("Starting thread...");
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, NULL, 0, NULL);
    }
    else if (reason == 0)
    {
    }
    return true;
}
