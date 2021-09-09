#pragma once
#include "Tessellator.h"

struct ScreenContext
{
private:
    char padding_48[48];

public:
    class Color *shaderColor;

private:
    char padding_176[120];

public:
    class Tessellator *tessellator;
};