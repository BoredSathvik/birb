#include "./Mouse_hook.h"

MouseHook::MouseHook() : Hook(std::string("mouse_hook"), std::string("48 ?? ?? 48 ?? ?? ?? 48 ?? ?? ?? 48 ?? ??  ?? ?? 41 ?? 41 ?? 41 ?? 41 ?? 48 ?? ?? ?? 44 ?? ??  ?? ??  ?? ??  ?? ?? 48 ?? ?? 44")) {}

void MouseHook::HookFunc()
{
    this->AutoHook(MouseHookCallBack, &func_original);
}

void MouseHook::MouseHookCallBack(void *parm_1, char button, char state, short mouse_x, short mouse_y, short movement_x, short movement_y, char parm_8)
{
    auto io = ImGui::GetIO();

    Logger::LogF("MouseHook called");

    return PLH::FnCast(func_original, MouseHookCallBack)(parm_1, button, state, mouse_x, mouse_y, movement_x, movement_y, parm_8);
}
