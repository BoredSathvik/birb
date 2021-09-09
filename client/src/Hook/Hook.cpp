#include "Hook.h"

KeyInput KeyOG = NULL;
MouseInput MouseOG = NULL;
Renderer RenderOG = NULL;
LevelRenderer LevelRendererOG = NULL;

void __fastcall KeyHook(int key, bool pressed)
{
    for (auto i : ModuleManager::getModules())
    {
        if (i->enabled)
        {
            i->OnKey(key, pressed);
        }
    }
    return KeyOG(key, pressed);
}

void __fastcall MouseHook(__int64 a1, char button, char down, short mouseX, short mouseY, short relativeX, short relativeY, char a8)
{
    for (auto i : ModuleManager::getModules())
    {
        if (i->enabled)
        {
            i->OnMouse(button, down, mouseX, mouseY);
        }
    }
    return MouseOG(a1, button, down, mouseX, mouseY, relativeX, relativeY, a8);
}

void __fastcall RendererHook(class ScreenView *screenView, MinecraftUIRenderContext *context)
{
    for (auto i : ModuleManager::getModules())
    {
        if (i->enabled)
        {
            i->OnRender(context);
        }
    }

    return RenderOG(screenView, context);
}

void __fastcall LevelRendererHook(__int64 _this, __int64 a2, __int64 a3)
{
    for (auto i : ModuleManager::getModules())
    {
        if (i->enabled)
        {
            i->OnLevelRender();
        }
    }

    return LevelRendererOG(_this, a2, a3);
}
Hook::Hook()
{
    MH_CreateHook((void *)Mem::AOBScan("?? 89 5C 24 08 57 ?? 83 EC 30 ?? 05 ?? ?? ?? ?? 8B DA"), &KeyHook, (void **)&KeyOG);
    MH_CreateHook((void *)Mem::AOBScan("48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F B7 BC 24 ?? ?? ?? ?? 48 8B D9"), &MouseHook, (void **)&MouseOG);
    MH_CreateHook((void *)Mem::AOBScan("48 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 B8 0F 29 78 A8 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B FA 48 89 54 24 ?? 4C 8B E9"), &RendererHook, (void **)&RenderOG);
    MH_CreateHook((void *)Mem::AOBScan("48 89 5C 24 10 48 89 74 24 20 57 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 ?? ?? ?? ?? 49 8B F8 48 8B DA"), &LevelRendererHook, (void **)&LevelRendererOG);
}

void Hook::Enable()
{
    MH_EnableHook(MH_ALL_HOOKS);
}

void Hook::Disable()
{
    MH_DisableHook(MH_ALL_HOOKS);
}