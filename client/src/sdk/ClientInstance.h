#pragma once
#include "MinecraftGame.h"
#include "GuiData.h"

struct ClientInstance
{
private:
    char padding_168[168];

public:
    MinecraftGame *minecraftGame;

private:
    char padding_320[144];

public:
    class LocalPlayer *clientPlayer;

private:
    char padding_1240[912];

public:
    GuiData *guiData;
};