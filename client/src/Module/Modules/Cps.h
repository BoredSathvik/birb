#pragma once

#include <string>
#include <vector>
#include "../Module.h"

class Cps : public Module
{
public:
    int rClicks;
    int lClicks;
    std::vector<int> rcps;
    std::vector<int> lcps;

    Cps() : Module("Cps"){};
    bool OnMouse(char button, char down, short mX, short mY) override;
    void OnRender(MinecraftUIRenderContext *ctx) override;
};