#pragma once

#include <chrono>
#include <string>

#include "../../../Lib/imgui/imgui.h"
#include "../../utils/global.h"
#include "../../utils/logger.h"
#include "../module.h"

using namespace std::chrono;

class CPSMod : public Module {
   public:
    CPSMod();
    ~CPSMod();

   private:
    milliseconds last;

    int clicks[10] = {};
    int current = 0;

    void OnInit() override;

    bool OnMouse(char button, char state, int x, int y) override;
    void OnHUDRender() override;
};