#pragma once

#include "../../../Lib/imgui/imgui.h"
#include "../../../Lib/imgui/imgui_internal.h"
#include "../../module/module_manager.h"
#include "../assets/fonts/IconsMaterialDesign.h"

class ConsoleMenu
{
public:
    static void Render();

private:
    static void ScrollBar(float offset);
};