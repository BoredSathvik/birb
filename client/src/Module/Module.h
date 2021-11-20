#pragma once

#include <string>
#include "../SDK/MinecraftUIRenderContext.h"

class Module
{

public:
    Module(std::string name);
    virtual ~Module();

    std::string name;
    bool enabled;

    void Toggle();

    virtual void onUIFrame(MinecraftUIRenderContext *renderCTX);
    virtual bool onKey(bool keyMap[254], int key, bool pressed);
};
