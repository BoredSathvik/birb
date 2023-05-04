#pragma once

#include "../hook.h"

class MouseHook : public Hook
{
  private:
    static void MouseHookCallback(void *parm_1, char button, char state, short mouse_x, short mouse_y, short movement_x,
                                  short movement_y, char parm_8);

  public:
    typedef void(__thiscall *Mouse)(void *a1, char mouseButton, char isDown, short mouseX, short mouseY,
                                    short relativeMovementX, short relativeMovementY, char a8);
    static inline Mouse func_original = 0;

    MouseHook();
    void HookFunc() override;
};