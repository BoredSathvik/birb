#include "./mouse_hook.h"

MouseHook::MouseHook() : Hook(std::string("mouse_hook"), std::string("48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F B7 BC 24")) {}

void MouseHook::HookFunc()
{
    this->AutoHook(MouseHookCallBack, &func_original);
}

void MouseHook::MouseHookCallBack(void *parm_1, char button, char state, short mouse_x, short mouse_y, short parm_6, short parm_7, char parm_8)
{
    auto io = ImGui::GetIO();

    if (button == 0) // Mouse Movement
    {
        io.AddMousePosEvent(mouse_x, mouse_y);
    }
    else if (button == 4) // Mouse Wheel Up or Down
    {
        io.AddMouseWheelEvent(0.0f, state / WHEEL_DELTA);
    }
    else // Mouse Button
    {
        io.AddMouseButtonEvent(button - 1, state);
    }

    if (!io.WantCaptureMouse)
        return PLH::FnCast(func_original, MouseHookCallBack)(parm_1, button, state, mouse_x, mouse_y, parm_6, parm_7, parm_8);
}
