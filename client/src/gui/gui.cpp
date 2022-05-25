#include "gui.h"

Gui::Gui()
{
    this->dx_manager = std::make_shared<DxManager>();
}

Gui::~Gui()
{
    Global::running = false;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Init()
{

    ImGui::CreateContext();

    HWND window = FindWindowA(nullptr, "Minecraft");

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(dx_manager->d3d_device.get(), dx_manager->d3d_context.get());

    std::thread render_thread(Render, dx_manager.get());
    // Logger::LogF(std::string("Reander thread id: ").append(std::to_string(render_thread.get_id())));
    render_thread.detach();

    Logger::LogF("Gui initialized");

    UIThread::RunOnUIThreadAsync(
        [&]
        {
            CoreWindow::GetForCurrentThread().SizeChanged({dx_manager.get(), &DxManager::OnWindowResize});
        });
}

void Render(DxManager *dx_manager)
{

    auto context = dx_manager->d2d_context.get();

    winrt::com_ptr<ID2D1SolidColorBrush> rect_brush;
    context->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.5f), rect_brush.put());

    while (true)
    {
        if (!dx_manager->resizing)
        {

            // context->BeginDraw();
            // context->SetTransform(D2D1::Matrix3x2F::Identity());

            // context->FillRoundedRectangle(
            //     D2D1::RoundedRect(D2D1::RectF(100.0f, 100.0f, 600.0f, 600.0f), 15, 15),
            //     rect_brush.get());

            // if (Logger::ErrorF(context->EndDraw(), "[Error] Failed to end draw"))
            // {
            //     return;
            // }

            // Logger::LogF("Render Thread");

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            bool show_window = true;
            ImGui::ShowDemoWindow(&show_window);

            ImGui::Render();
            float color[4] = {0.0f, 0.0f, 0.0f, 0.3f};
            dx_manager->d3d_context->OMSetRenderTargets(1, dx_manager->d3d_render_target_view.put(), nullptr);
            dx_manager->d3d_context->ClearRenderTargetView(dx_manager->d3d_render_target_view.get(), color);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            dx_manager->swapchain->Present(1, 0);
        }
    }
}