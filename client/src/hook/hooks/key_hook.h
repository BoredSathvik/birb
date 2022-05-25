#include "../hook.h"
#include "../../../Lib/imgui/imgui.h"
#include "../../../Lib/imgui/imgui_impl_win32.h"

class KeyHook : public Hook
{
    static void KeyHookCallBack(int key, int state);

public:
    static inline uintptr_t func_original = 0;
    KeyHook();
    void HookFunc() override;
};