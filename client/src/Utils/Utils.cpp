#include "Utils.h"

void UnLoad()
{
    Sleep(100);
    FreeLibraryAndExitThread(Utils::hMod, 0);
}

void Utils::UnInject()
{
    Utils::DebugF("Removing Hooks");
    HookManager::RemoveHooks();
    Utils::DebugF("Removing modules");
    ModuleManager::RemoveModules();

    Utils::DebugF("Freeing Library");
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UnLoad, NULL, 0, NULL);
}

void Utils::DebugF(const char *out)
{
    std::string dir = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + std::string("Birb_Logs.txt"));

    CloseHandle(CreateFileA(dir.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

    std::ofstream logs;
    logs.open(dir.c_str(), std::ios_base::app);
    logs << out << std::endl;
    logs.close();
}

void Utils::DebugF(const std::string out)
{
    Utils::DebugF(out.c_str());
}
