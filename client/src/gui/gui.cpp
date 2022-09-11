// Primary color #EF6C00
// Danger color #dc3545
// Success color #28A745
// Warning color #FFC107

#include "gui.h"

Gui::Gui() { this->dx_manager = new DxManager(); }

void Gui::Init() {
    HWND window;
    UIThread::RunOnUIThreadAsync([&] { CoreWindow::GetForCurrentThread().as<ICoreWindowInterop>()->get_WindowHandle(&window); }).get();

    ImGui::CreateContext();

    InitStyle();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(dx_manager->d3d_device.get(), dx_manager->d3d_context.get());

    // dx_manager->d2d_context.get()->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), rect_brush.put());

    Logger::LogF("Gui initialized");
}
void Gui::CleanGui() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // this->rect_brush = nullptr;
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

    // ImGui::ShowDemoWindow();
    // ImGui::ShowStyleEditor();
    // ImGui::ShowFontAtlas(ImGui::GetIO().Fonts);

    // if (*this->show_gui && this->show) {

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
        // } else if (*this->show_hud) {
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
    // dx_manager->d3d_context->ClearDepthStencilView(dx_manager->d3d_depth_stencil_view.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
void Gui::RenderBackground() {
    // struct Vertex {
    //     float x;
    //     float y;
    // };

    // const Vertex vertices[] = {{0.0f, 0.5f}, {0.5f, -0.5f}, {-0.5, -0.5f}};

    // winrt::com_ptr<ID3D11Buffer> vertex_buffer;
    // D3D11_BUFFER_DESC bd = {};
    // bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    // bd.Usage = D3D11_USAGE_DEFAULT;
    // bd.CPUAccessFlags = 0;
    // bd.MiscFlags = 0;
    // bd.ByteWidth = sizeof(vertices);
    // bd.StructureByteStride = sizeof(Vertex);

    // D3D11_SUBRESOURCE_DATA sd = {};
    // sd.pSysMem = vertices;

    // dx_manager->d3d_device->CreateBuffer(&bd, &sd, vertex_buffer.put());

    // // Binds vertex buffer to pipeline
    // u_int stride = sizeof(Vertex);
    // u_int offset = 0;
    // dx_manager->d3d_context->IASetVertexBuffers(0, 1, vertex_buffer.put(), &stride, &offset);

    // // vertex shader
    // winrt::com_ptr<ID3DBlob> blob;
    // winrt::com_ptr<ID3D11PixelShader> pixel_shader;
    // D3DReadFileToBlob(L"C:/Users/sathv/AppData/Local/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalCache/birb/shaders/ps.cso", blob.put());
    // dx_manager->d3d_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixel_shader.put());
    // dx_manager->d3d_context->PSSetShader(pixel_shader.get(), nullptr, 0);

    // // vertex shader
    // winrt::com_ptr<ID3D11VertexShader> vertex_shader;
    // D3DReadFileToBlob(L"C:/Users/sathv/AppData/Local/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/LocalCache/birb/shaders/vs.cso", blob.put());
    // dx_manager->d3d_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertex_shader.put());
    // dx_manager->d3d_context->VSSetShader(vertex_shader.get(), nullptr, 0);

    // // Creates input layout for the vertex shader
    // winrt::com_ptr<ID3D11InputLayout> input_layout;
    // const D3D11_INPUT_ELEMENT_DESC ied[] = {{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    // dx_manager->d3d_device->CreateInputLayout(ied, (u_int)std::size(ied), blob->GetBufferPointer(), blob->GetBufferSize(), input_layout.put());
    // dx_manager->d3d_context->IASetInputLayout(input_layout.get());

    // // sets topology
    // dx_manager->d3d_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // // sets rendertarget to rendertarget ez

    // // draws everything
    // dx_manager->d3d_context->Draw((u_int)std::size(vertices), 0);
}