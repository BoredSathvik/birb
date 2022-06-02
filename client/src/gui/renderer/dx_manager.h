#pragma once

#include <windows.h>
#include <math.h>

#include <winrt/base.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.UI.Core.h>

#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include <wincodec.h>

#include "../../utils/logger.h"

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Graphics::Display;
using namespace winrt::Windows::System;

class DxManager
{
public:
    DxManager();

    void OnWindowResize(CoreWindow const &, WindowSizeChangedEventArgs const &args);

    // private:
    float dpi = 96.0f;
    float resizing = false;

    winrt::com_ptr<ID3D11Device3> d3d_device;
    winrt::com_ptr<ID3D11DeviceContext3> d3d_context;
    winrt::com_ptr<IDXGISwapChain1> swapchain;

    winrt::com_ptr<ID3D11RenderTargetView> d3d_render_target_view;
    winrt::com_ptr<ID3D11DepthStencilView> d3d_depth_stencil_view;
    D3D11_VIEWPORT screen_viewport;

    // winrt::com_ptr<ID2D1Factory3> d2d_factory;
    // winrt::com_ptr<ID2D1Device2> d2d_device;
    // winrt::com_ptr<ID2D1DeviceContext2> d2d_context;
    // winrt::com_ptr<ID2D1Bitmap1> d2d_target_bitmap;

    // winrt::com_ptr<IDWriteFactory3> dwrite_factory;
    // winrt::com_ptr<IWICImagingFactory2> m_wic_factory;

private:
    void CreateSwapChain();
    void CreateD2DResources();
    void CreateSwapChainResources();
};
