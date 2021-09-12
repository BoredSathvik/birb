#pragma once

#include <string>
#include <vector>
#include "../Module.h"

class Fps : public Module
{
public:
    unsigned int frames = 0;
    unsigned int times = 0;
    unsigned int fps = 0;

    Fps() : Module("Fps"){};
    void OnRender(MinecraftUIRenderContext *ctx) override;
    void OnLevelRender() override;
};