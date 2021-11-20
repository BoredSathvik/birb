#pragma once

#include "../Module.h"

class AutoGG : public Module
{

public:
    AutoGG();
    ~AutoGG();
    bool onKey(bool keyMap[254], int key, bool pressed) override;
};
