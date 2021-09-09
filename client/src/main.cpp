#include <Windows.h>
#include <thread>

#include "utils/Mem.h"
#include "utils/MinHook.h"
#include "Hook/Hook.h"
#include "Module/ModuleManager.h"

bool isRunning = false;
//uintptr_t modBase = (uintptr_t)GetModuleHandle("Minecraft.Windows.exe");
//float *fov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x18});
//float *minFov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x10});
//float fov_before = 0;
//bool zom = false;

// typedef void(__fastcall *KeyInput)(int key, bool pressed);
// typedef void(__fastcall *MouseInput)(__int64 a1, char button, char down, short mouseX, short mouseY, short relativeX, short relativeY, char a8);
// typedef void(__fastcall *Renderer)(class ScreenView *screenView, class MinecraftUIRenderContext *context);

void start()
{
    //Key Pattern = ?? 89 5C 24 08 57 ?? 83 EC 30 ?? 05 ?? ?? ?? ?? 8B DA
    //Mouse Pattern = 48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F B7 BC 24 ?? ?? ?? ?? 48 8B D9
    //Render Pattern = 48 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B FA 48 89 54 24 ?? 4C 8B E9

    ModuleManager::InitModules();

    MH_Initialize();

    Hook hooks = Hook();
    hooks.Enable();

    std::thread([]
                {
                    auto cps = (Cps *)ModuleManager::getModuleByName("Cps");
                    auto fps = (Fps *)ModuleManager::getModuleByName("Fps");
                    while (isRunning)
                    {

                        fps->frames++;
                        fps->times++;

                        if (fps->times >= 10)
                        {
                            fps->fps = fps->frames;
                            fps->frames = 0;
                            fps->times = 0;
                        }
                        if (cps->lcps.size() >= 10)
                        {
                            cps->lcps.erase(cps->lcps.begin());
                        }

                        cps->lcps.emplace_back(cps->lClicks);
                        cps->lClicks = 0;

                        if (cps->rcps.size() >= 10)
                        {
                            cps->rcps.erase(cps->rcps.begin());
                        }

                        cps->rcps.emplace_back(cps->rClicks);
                        cps->rClicks = 0;

                        Sleep(100);
                    }
                })
        .detach();
}

BOOL __stdcall DllMain(HMODULE hModule, int reason, void *)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        isRunning = true;
        std::thread t(start);
        t.detach();
        DisableThreadLibraryCalls(hModule);
    }
    break;
    case DLL_PROCESS_DETACH:
        isRunning = false;
        MH_Uninitialize();
        break;
    }
    return 1;
}
