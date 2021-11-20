#pragma once

#include "../Hook.h"
#include "../../SDK/MinecraftUIRenderContext.h"
#include "../../Module/ModuleManager.h"

class UIRenderer : public Hook
{
    static inline uint64_t UIRendererOG = 0;
    static void __fastcall UIRendererCB(void *a1, MinecraftUIRenderContext *UIRenderCTX);

public:
    UIRenderer();
    bool run() override;
};