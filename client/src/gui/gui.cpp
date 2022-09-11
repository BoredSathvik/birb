#include "gui.h"

Gui::Gui() { this->dx_manager = new DxManager(); }

void Gui::Init() {
    HWND window;
    UIThread::RunOnUIThreadAsync([&] { CoreWindow::GetForCurrentThread().as<ICoreWindowInterop>()->get_WindowHandle(&window); }).get();

    ImGui::CreateContext();

    InitStyle();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(dx_manager->d3d_device.get(), dx_manager->d3d_context.get());

    Logger::LogF("Gui initialized");
}
void Gui::CleanGui() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    delete this->dx_manager;
}

bool Gui::OnKey(int key, int state, bool keys[256]) {
    static BYTE key_state[256] = {0};

    auto io = &ImGui::GetIO();

    // Sets the modifier keys
    io->AddKeyEvent(ImGuiKey_ModCtrl, keys[VK_CONTROL]);
    io->AddKeyEvent(ImGuiKey_ModShift, keys[VK_SHIFT]);
    io->AddKeyEvent(ImGuiKey_ModAlt, keys[VK_MENU]);
    io->AddKeyEvent(ImGuiKey_ModSuper, keys[VK_APPS]);

    key_state[key] = state << 7;

    if (state == 1) {
        // Sets the num lock key
        if (key == VK_NUMLOCK) key_state[VK_NUMLOCK] |= !keys[VK_NUMLOCK];

        // Sets the caps lock key
        if (key == VK_CAPITAL) key_state[VK_CAPITAL] |= !keys[VK_CAPITAL];

        unsigned short input_char = 0;
        ToAscii(key, NULL, key_state, &input_char, 0);

        if (input_char > 0) {
            io->AddInputCharacter(input_char);
        }
    }

    io->AddKeyEvent(Gui::VKToImGuiKey(key), state);

    if ((key == 'E' && state == 1) && (keys[VK_CONTROL])) {
        this->show = !this->show;
        return true;
    }
    if (this->show && (key == VK_ESCAPE && state == 1)) {
        this->show = false;
        return true;
    }

    if (io->WantCaptureKeyboard) return true;
    return false;
}

bool Gui::OnMouse(char button, char state, int x, int y) {
    auto io = &ImGui::GetIO();

    switch (button) {
        case 0:
            io->AddMousePosEvent(x, y);
            break;
        case 1:
        case 2:
        case 3:
            io->AddMouseButtonEvent(button - 1, state);
            break;
        case 4:
            io->AddMouseWheelEvent(0.0f, state / WHEEL_DELTA);
            break;
        default:
            io->AddMouseWheelEvent(button - 2, state);
            break;
    }

    if (io->WantCaptureMouse) return true;
    return false;
}

void Gui::InitStyle() {
    auto io = &ImGui::GetIO();
    io->Fonts->AddFontFromMemoryCompressedBase85TTF(inter_bold_compressed_data_base85, 24.0f);
    io->Fonts->AddFontFromMemoryCompressedBase85TTF(inter_compressed_data_base85, 24.0f);
    io->Fonts->AddFontFromMemoryCompressedBase85TTF(inter_bold_compressed_data_base85, 40.0f);
    io->Fonts->AddFontFromMemoryCompressedBase85TTF(inter_bold_compressed_data_base85, 26.0f);

    ImWchar ranges[] = {0x1, (unsigned short)0x1FFFF, 0};

    io->Fonts->AddFontFromMemoryCompressedBase85TTF(material_icons_compressed_data_base85, 24.0f, nullptr, ranges);
    io->Fonts->Build();

    auto style = &ImGui::GetStyle();

    style->Alpha = 0.90f;

    style->WindowRounding = 20.0f;
    style->FrameRounding = 10.0f;
    style->ChildRounding = 10.0f;
    style->GrabRounding = 5.0f;

    style->WindowPadding = ImVec2(0.0f, 0.0f);
    style->ItemSpacing = ImVec2(10.0f, 10.0f);

    style->ScrollbarSize = 20.0f;

    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.80f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.80f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.75f, 0.75f, 0.75f, 0.80f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
}

void Gui::Render() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float width = 1000.0f;
    float height = 650.0f;
    float x = (dx_manager->window_size[0] / 2) - (width / 2);
    float y = (dx_manager->window_size[1] / 2) - (height / 2);

    Global::width = dx_manager->window_size[0];
    Global::height = dx_manager->window_size[1];

    if (this->show) {
        bool open = true;
        ImGui::SetNextWindowPos(ImVec2(x, y));
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::Begin("Main menu", &open,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), ImColor(0.0f, 0.0f, 0.0f, 0.80f), 20.0f, ImDrawFlags_RoundCornersAll);

        // Start of Nav Window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 20.0f));
        ImGui::BeginChild("Navigation", ImVec2(width / 5, height), true, ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar();
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + (width / 5), y + height), ImColor(0.12f, 0.12f, 0.12f, 0.80f), 20.0f,
                                 ImDrawFlags_RoundCornersLeft);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
        ImGui::Text("Birb");
        ImGui::PopFont();

        draw_list->AddLine(ImVec2(x + 25, y + 70), ImVec2(x + 25 + 150, y + 70), ImColor(0.5f, 0.5f, 0.5f, 0.80f), 1.0f);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30.0f);

        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.14f, 0.14f, 0.14f, 0.80f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.17f, 0.17f, 0.17f, 0.80f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.22f, 0.22f, 0.22f, 0.80f));

        if (ImGui::Button("Modules", ImVec2(180, 50.0f))) curr_menu = Menus::Modules;
        if (ImGui::Button("Settings", ImVec2(180, 50.0f))) curr_menu = Menus::Settings;
        if (ImGui::Button("HUD Editor", ImVec2(180, 50.0f))) curr_menu = Menus::HUDEditor;
        if (ImGui::Button("Console", ImVec2(180, 50.0f))) curr_menu = Menus::Console;
        if (ImGui::Button("Change Log", ImVec2(180, 50.0f))) curr_menu = Menus::ChangeLog;

        ImGui::PopStyleColor(3);

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 100);

        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.70f, 0.0f, 0.0f, 0.80f));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.90f, 0.0f, 0.0f, 0.80f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.80f));
        if (ImGui::Button("Unload", ImVec2(180, 50.0f))) {
            Global::running = false;
        }
        ImGui::PopStyleColor(3);

        ImGui::EndChild();
        // End of Nav Window

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
        ImGui::SameLine();
        ImGui::PopStyleVar();

        // Start of Content Window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30.0f, 30.0f));
        ImGui::BeginChild("Content", ImVec2((width / 5) * 4, height), true, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleVar();
        draw_list->AddRectFilled(ImVec2(x + (width / 5), y), ImVec2(x + width, y + height), ImColor(0.0f, 0.0f, 0.0f, 0.0f), 20.0f,
                                 ImDrawFlags_RoundCornersRight);

        switch (curr_menu) {
            case Menus::Modules:
                ModuleMenu::Render();
                break;
            case Menus::Settings:
                ImGui::Text("WIP");
                break;
            case Menus::HUDEditor:
                ImGui::Text("WIP");
                break;
            case Menus::Console:
                ConsoleMenu::Render();
                break;
            case Menus::ChangeLog:
                ImGui::Text("WIP");
                break;
        }

        ImGui::EndChild();
        // End of Content Window

        ImGui::End();
    } else if (true) {
        for (auto module : *ModuleManager::GetInstance()->modules) {
            module->OnHUDRender();
        }
    }

    ImGui::Render();

    float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    ID3D11RenderTargetView* targets[1] = {dx_manager->d3d_render_target_view.get()};
    dx_manager->d3d_context->OMSetRenderTargets(1, targets, nullptr);
    dx_manager->d3d_context->ClearRenderTargetView(dx_manager->d3d_render_target_view.get(), color);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
