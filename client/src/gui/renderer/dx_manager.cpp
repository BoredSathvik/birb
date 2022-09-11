#define ENABLE_DEBUG_LAYER

#include "dx_manager.h"

#include <unknwn.h>

DxManager::DxManager() {
    Logger::LogF("BOI WTF");
    CreateDevice();
    CreateRenderTargetView();

    UIThread::RunOnUIThreadAsync([&] {
        auto window = CoreWindow::GetForCurrentThread();
        resize_token = window.SizeChanged({this, &DxManager::OnWindowResize});

        dpi = DisplayInformation::GetForCurrentView().LogicalDpi();

        float width = window.Bounds().Width * 96.0f / dpi;
        float height = window.Bounds().Height * 96.0f / dpi;

        this->window_size[0] = width;
        this->window_size[1] = height;
    }).get();
}

DxManager::~DxManager() {
    d3d_render_target_view = nullptr;

    swapchain = nullptr;
    d3d_context = nullptr;
    d3d_device = nullptr;

    UIThread::RunOnUIThreadAsync([&] { CoreWindow::GetForCurrentThread().SizeChanged(resize_token); }).get();
}

void DxManager::CreateDevice() {
    UINT creation_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(ENABLE_DEBUG_LAYER)
    creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
                                          D3D_FEATURE_LEVEL_9_3,  D3D_FEATURE_LEVEL_9_2,  D3D_FEATURE_LEVEL_9_1};

    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11DeviceContext> context;

    D3D_FEATURE_LEVEL feature_level;

    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creation_flags, feature_levels, ARRAYSIZE(feature_levels), D3D11_SDK_VERSION,
                                 device.put(), &feature_level, context.put()))) {
        Logger::LogF("[Error] Failed to create device and context");
        return;
    }

    d3d_device = device.as<ID3D11Device3>();
    d3d_context = context.as<ID3D11DeviceContext3>();

    winrt::com_ptr<IDXGIDevice3> dxgi_device;
    dxgi_device = d3d_device.as<IDXGIDevice3>();

    winrt::com_ptr<IDXGIAdapter> dxgi_adapter;
    if (FAILED(dxgi_device->GetAdapter(dxgi_adapter.put()))) {
        Logger::LogF("[Error] Failed to get DXGI adapter");
        return;
    };
    winrt::com_ptr<IDXGIFactory2> dxgi_factory;
    if (FAILED(dxgi_adapter->GetParent(IID_PPV_ARGS(dxgi_factory.put())))) {
        Logger::LogF("[Error] Failed to get DXGI factory");
        return;
    }

    DXGI_SWAP_CHAIN_DESC1 swapchain_desc = {};
    swapchain_desc.Width = 0;
    swapchain_desc.Height = 0;
    swapchain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapchain_desc.Stereo = false;
    swapchain_desc.SampleDesc.Count = 1;
    swapchain_desc.SampleDesc.Quality = 0;
    swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchain_desc.BufferCount = 2;
    swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapchain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER;
    swapchain_desc.Scaling = DXGI_SCALING_NONE;
    swapchain_desc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

    if (Logger::ErrorF(dxgi_factory->CreateSwapChainForCoreWindow(d3d_device.get(), winrt::get_unknown(CoreApplication::MainView().CoreWindow()),
                                                                  &swapchain_desc, nullptr, swapchain.put()),
                       "[Error] Failed to create swapchain")) {
        return;
    }

    if (FAILED(dxgi_device->SetMaximumFrameLatency(1))) {
        Logger::LogF("[Error] Failed to set maximum frame latency");
        return;
    };
}

void DxManager::CreateRenderTargetView() {
    winrt::com_ptr<ID3D11Texture2D> back_buffer;
    if (FAILED(swapchain->GetBuffer(0, IID_PPV_ARGS(back_buffer.put())))) {
        Logger::LogF("[Error] Failed to get back_buffer");
        return;
    }

    if (FAILED(d3d_device->CreateRenderTargetView(back_buffer.get(), nullptr, d3d_render_target_view.put()))) {
        Logger::LogF("[Error] Failed to create render_target_view");
        return;
    };

    D3D11_TEXTURE2D_DESC back_buffer_desc = {};
    back_buffer->GetDesc(&back_buffer_desc);

    CD3D11_TEXTURE2D_DESC depth_stencil_desc(DXGI_FORMAT_D24_UNORM_S8_UINT, back_buffer_desc.Width, back_buffer_desc.Height,
                                             1,  // This depth stencil view has only one texture.
                                             1,  // Use a single mipmap level.
                                             D3D11_BIND_DEPTH_STENCIL);

    winrt::com_ptr<ID3D11Texture2D> depth_stencil;
    if (FAILED(d3d_device->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil.put()))) {
        Logger::LogF("[Error] Failed to create depth_stencil");
        return;
    }
    screen_viewport = CD3D11_VIEWPORT(0.0f, 0.0f, back_buffer_desc.Width, back_buffer_desc.Height);

    d3d_context->RSSetViewports(1, &screen_viewport);
    resizing = false;
}

void DxManager::OnWindowResize(CoreWindow const &, WindowSizeChangedEventArgs const &args) {
    resizing = true;

    d3d_context->OMSetRenderTargets(0, nullptr, nullptr);
    d3d_render_target_view = nullptr;

    float dpi = DisplayInformation::GetForCurrentView().LogicalDpi();

    float width = args.Size().Width * 96.0f / dpi;
    float height = args.Size().Height * 96.0f / dpi;

    if (Logger::ErrorF(swapchain->ResizeBuffers(2, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER),
                       "[Error] Failed to resize buffers"))
        return;

    this->window_size[0] = width;
    this->window_size[1] = height;

    CreateRenderTargetView();
}
