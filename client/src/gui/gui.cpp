#include "gui.h"

Gui::Gui()
{
    this->dx_manager = std::make_shared<DxManager>();
}

Gui::~Gui()
{
}

void Gui::Init()
{
    ImGui::CreateContext();

    HWND window;
    UIThread::RunOnUIThreadAsync(
        [&]
        {
            CoreWindow::GetForCurrentThread().as<ICoreWindowInterop>()->get_WindowHandle(&window);
        })
        .get();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(dx_manager->d3d_device.get(), dx_manager->d3d_context.get());

    std::thread render_thread(Render);
    render_thread.detach();

    Logger::LogF("Gui initialized");
}

void Gui::CleanGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void Render()
{
    Gui *gui = Gui::GetInstance();
    while (Global::running)
    {
        if (!gui->dx_manager->resizing)
        {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::ShowDemoWindow(&gui->show_window);

            ImGui::Render();
            float color[4] = {0.0f, 0.0f, 0.0f, 0.3f};
            gui->dx_manager->d3d_context->OMSetRenderTargets(1, gui->dx_manager->d3d_render_target_view.put(), nullptr);
            gui->dx_manager->d3d_context->ClearRenderTargetView(gui->dx_manager->d3d_render_target_view.get(), color);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            gui->dx_manager->swapchain->Present(1, 0);
        }
    }
    Global::should_exit = true;
}