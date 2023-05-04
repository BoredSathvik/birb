#pragma once

#include "../hook.h"

class KeyHook : public Hook
{
  private:
    static inline bool keys[256] = {false};

    static void KeyHookCallback(int key, int state);

  public:
    typedef void(__thiscall *KeyBoard)(uint64_t keyId, bool held);
    static inline KeyBoard func_original = 0;

    KeyHook();
    void HookFunc() override;
};
