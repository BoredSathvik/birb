#pragma once

#include <string>
#include "../sdk/MinecraftUIRenderContext.h"

class Module
{
public:
    bool enabled;
    std::string name;

public:
    Module(std::string name)
    {
        this->name = name;
        this->enabled = true;
    };
    virtual void OnEnable(){};
    virtual void OnDisable(){};
    virtual void OnTick(){};
    virtual void OnKey(int key, bool pressed){};
    virtual bool OnMouse(char button, char down, short mX, short mY) { return false; };
    virtual void OnRender(MinecraftUIRenderContext *ctx){};
    virtual void OnLevelRender(){};
};