#pragma once

#include "../Utils/MathUtils.h"

struct GuiData
{
private:
    char padding_0[24];

public:
    Vec2<float> resolution;
    float widthReal2;  //0x0020
    float heightReal2; //0x0024
    Vec2<float> scaledResolution;
    char padding_56[8];
    float scale;
};