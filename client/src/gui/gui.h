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
private:
    std::shared_ptr<DxManager> dx_manager;

public:
    Gui();
    ~Gui();
    static Gui *GetInstance()
    {
        static Gui *instance = new Gui();
        return instance;
    };

    void Init();
};

void Render(DxManager *dx_manager);