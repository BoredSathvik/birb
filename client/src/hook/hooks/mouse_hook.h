#pragma once

#include "../hook.h"
#include "../../../Lib/imgui/imgui.h"

class MouseHook : public Hook
{
    static void MouseHookCallBack(void *parm_1, char button, char state, short mouse_x, short mouse_y, short movement_x, short movement_y, char parm_8);

public:
    static inline uintptr_t func_original = 0;

    MouseHook();

    void HookFunc() override;
};