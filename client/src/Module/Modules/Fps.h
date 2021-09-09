#pragma once

#include <string>
#include <vector>
#include "../Module.h"

class Fps : public Module
{
public:
    unsigned int frames;
    unsigned int times;
    unsigned int fps;

    Fps() : Module("Fps"){};
    void OnRender(MinecraftUIRenderContext *ctx) override;
    void OnLevelRender() override;
};