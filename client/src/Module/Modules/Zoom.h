#pragma once

#include "../Module.h"
#include "../../Utils/Mem.h"
#include "../../Utils/Utils.h"

class Zoom : public Module
{
public:
    uintptr_t modBase = (uintptr_t)GetModuleHandle("Minecraft.Windows.exe");
    float *fov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x18});
    float *sen = (float *)Mem::FindDMAAddy((modBase + 0x4074618), {0x28, 0xCA8, 0x20, 0x0, 0x14});
    float *minFov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x10});
    float fov_before = 0;
    float sen_before = 0;
    bool zoom = false;

    Zoom() : Module("Zoom"){};
    void OnKey(int key, bool pressed) override;
    bool OnMouse(char button, char down, short mX, short mY) override;
};