#pragma once

#include "../Module.h"
#include "../../Utils/Mem.h"

class Zoom : public Module
{
public:
    uintptr_t modBase = (uintptr_t)GetModuleHandle("Minecraft.Windows.exe");
    float *fov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x18});
    float *minFov = (float *)Mem::FindDMAAddy((modBase + 0x04074610), {0x18, 0x138, 0x10});
    float fov_before = 0;
    bool zoom = false;

    Zoom() : Module("Zoom"){};
    void OnKey(int key, bool pressed) override;
    void OnMouse(char button, char down, short mX, short mY) override;
};