#pragma once

#include <Windows.h>

#include "../Module.h"
#include "../../Utils/Utils.h"
#include "../../Module/ModuleManager.h"
#include "../../Hook/HookManager.h"

class UnInject : public Module
{

public:
    UnInject();
    ~UnInject();
    bool onKey(bool keyMap[254], int key, bool pressed) override;
};
