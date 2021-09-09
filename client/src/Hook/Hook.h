#pragma once

#include "../Utils/MinHook.h"
#include "../utils/Mem.h"
#include "../Module/ModuleManager.h"
#include "../sdk/MinecraftUIRenderContext.h"

typedef void(__fastcall *KeyInput)(int key, bool pressed);
typedef void(__fastcall *MouseInput)(__int64 a1, char button, char down, short mouseX, short mouseY, short relativeX, short relativeY, char a8);
typedef void(__fastcall *Renderer)(class ScreenView *screenView, class MinecraftUIRenderContext *context);
typedef void(__fastcall *LevelRenderer)(__int64 _this, __int64 a2, __int64 a3);

class Hook
{
public:
    Hook();
    void Enable();
    void Disable();
};