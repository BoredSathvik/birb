#pragma once

#include "../hook.h"
#include "../../../Lib/imgui/imgui.h"
#include "../../../Lib/imgui/imgui_impl_win32.h"
#include "../../utils/global.h"
#include "../hook_manager.h"

class KeyHook : public Hook
{
    static void KeyHookCallBack(int key, int state);

public:
    static inline uintptr_t func_original = 0;

    KeyHook();

    void HookFunc() override;

    static inline bool keys[256] = {false};
    // Used for imgui input
    static inline BYTE key_state[256] = {0};

    static ImGuiKey VKToImGuiKey(int key);
};
