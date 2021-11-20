#include "UIRenderer.h"

void __fastcall UIRenderer::UIRendererCB(void *a1, MinecraftUIRenderContext *UIRenderCTX)
{
    for (auto Module : *ModuleManager::Modules)
    {
        Module->onUIFrame(UIRenderCTX);
    }
    PLH::FnCast(UIRendererOG, UIRendererCB)(a1, UIRenderCTX);
}

UIRenderer::UIRenderer() : Hook::Hook("UIRenderer", "?? 8B C4 ?? 89 58 18 55 56 57 ?? 54 ?? 55 ?? 56 ?? 57 ?? 8D A8 98 FD FF FF ?? 81 EC 30 03 00 00 ?? ?? 70 B8 ?? ?? 78 A8 ?? 8B 05 91 FC 17 03") {}

bool UIRenderer::run()
{
    return this->hookFn(UIRendererCB, &UIRendererOG);
}