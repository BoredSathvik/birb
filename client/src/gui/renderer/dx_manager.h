#pragma once

#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <d3d11_3.h>
#include <dwrite_3.h>
#include <wincodec.h>

// Winrt headers
#include <windows.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/base.h>

#include "../../utils/logger.h"
#include "../../utils/ui_thread.h"

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Graphics::Display;

class DxManager
{
public:
    DxManager();
    ~DxManager();

    void OnWindowResize(CoreWindow const &, WindowSizeChangedEventArgs const &args);

    float dpi = 96.0f;
    bool resizing = false;
    float window_size[2] = {0.0f, 0.0f};

    // Direct3D objects.
    winrt::com_ptr<ID3D11Device3> d3d_device;
    winrt::com_ptr<ID3D11DeviceContext3> d3d_context;
    winrt::com_ptr<IDXGISwapChain1> swapchain;

    // Direct3D rendering objects. Required for 3D.
    winrt::com_ptr<ID3D11RenderTargetView> d3d_render_target_view;
    D3D11_VIEWPORT screen_viewport;

    // Direct2D drawing components.
    winrt::com_ptr<ID2D1Factory3> d2d_factory;
    winrt::com_ptr<ID2D1Device2> d2d_device;
    winrt::com_ptr<ID2D1DeviceContext2> d2d_context;

    winrt::com_ptr<ID2D1Bitmap1> d2d_target_bitmap;

    // DirectWrite drawing components.
    winrt::com_ptr<IDWriteFactory3> dwrite_factory;
    winrt::com_ptr<IWICImagingFactory2> wic_factory;

private:
    winrt::event_token resize_token;

    void CreateDevice();
    void CreateRenderTargetView();
};
