#pragma once

#include <thread>

#include <CoreWindow.h>

#include "../../Lib/imgui/imgui.h"
#include "../../Lib/imgui/imgui_impl_dx11.h"
#include "../../Lib/imgui/imgui_impl_win32.h"
#include "./renderer/dx_manager.h"
#include "../utils/ui_thread.h"
#include "../utils/global.h"

using namespace winrt::Windows::ApplicationModel::Core;

class Gui
{
public:
    std::shared_ptr<DxManager> dx_manager;
    bool show_window = true;

    Gui();
    ~Gui();
    static Gui *GetInstance()
    {
        static Gui instance;
        return &instance;
    };

    void Init();
    void CleanGui();
};

void Render();