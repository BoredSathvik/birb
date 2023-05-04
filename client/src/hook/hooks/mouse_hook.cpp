#include "./mouse_hook.h"

#include "../../gui/gui.h"
#include "../../module/module_manager.h"

MouseHook::MouseHook()
    : Hook(std::string("mouse_hook"),
           std::string(
               "48 8B C4 48 89 58 ?? 48 89 68 ?? 48 89 70 ?? 57 41 54 41 55 41 56 41 57 48 83 EC ?? 44 0F B7 BC 24"))
{
}

void MouseHook::HookFunc()
{
    this->AutoHook(MouseHookCallback, (void **)&func_original);
}

void MouseHook::MouseHookCallback(void *parm_1, char button, char state, short mouse_x, short mouse_y, short parm_6,
                                  short parm_7, char parm_8)
{
    bool block = false;

    block = Gui::GetInstance()->OnMouse(button, state, mouse_x, mouse_y) || block;

    for (auto mod : *ModuleManager::GetInstance()->modules)
    {
        block = mod->OnMouse(button, state, mouse_x, mouse_y) || block;
    }

    if (!block)
        return func_original(parm_1, button, state, mouse_x, mouse_y, parm_6, parm_7, parm_8);
}
