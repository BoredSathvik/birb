#pragma once

#include "../hook.h"

class KeyHook : public Hook {
   private:
    static inline bool keys[256] = {false};

    static void KeyHookCallback(int key, int state);

   public:
    static inline uintptr_t func_original = 0;

    KeyHook();
    void HookFunc() override;
};
