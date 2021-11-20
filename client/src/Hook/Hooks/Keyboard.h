#pragma once

#include "../Hook.h"
#include "../../Module/ModuleManager.h"
#include "../../Utils/Utils.h"

class Keyboard : public Hook
{
    static inline uint64_t KeyboardOG = 0;
    static void __fastcall KeyboardCB(int key, bool pressed);

public:
    Keyboard();
    ~Keyboard();
    bool run() override;
};