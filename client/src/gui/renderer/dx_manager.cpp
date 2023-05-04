#define ENABLE_DEBUG_LAYER

#include "dx_manager.h"

#include <unknwn.h>

DxManager::DxManager()
{
    CreateDevice();
    CreateRenderTargetView();

    UIThread::RunOnUIThreadAsync([&]
                                 {
        auto window = CoreWindow::GetForCurrentThread();
        resize_token = window.SizeChanged({this, &DxManager::OnWindowResize});

        dpi = DisplayInformation::GetForCurrentView().LogicalDpi();

        float width = window.Bounds().Width * 96.0f / dpi;
        float height = window.Bounds().Height * 96.0f / dpi;

        this->window_size[0] = width;
        this->window_size[1] = height; })
        .get();
}

DxManager::~DxManager()
{
    d2d_context->SetTarget(nullptr);
    d2d_target_bitmap = nullptr;

    d3d_render_target_view = nullptr;

    d2d_context = nullptr;
    d2d_device = nullptr;
    swapchain = nullptr;
    d3d_context = nullptr;
    d3d_device = nullptr;

    wic_factory = nullptr;
    dwrite_factory = nullptr;
    d2d_factory = nullptr;

    UIThread::RunOnUIThreadAsync([&]
                                 { CoreWindow::GetForCurrentThread().SizeChanged(resize_token); })
        .get();
}

void DxManager::CreateDevice()
{
    // d2d factory
#if defined(ENABLE_DEBUG_LAYER)
    D2D1_FACTORY_OPTIONS options;
    options.debugLevel = D2D1_DEBUG_LEVEL_ERROR;
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &options, d2d_factory.put_void())))
    {
        Logger::LogF("[Error] Failed to create D2D factory");
        return;
    }
#else
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(d2d_factory.put()))))
    {
        Logger::LogF("[Error] Failed to create D2D factory");
        return;
    }
#endif
    // dwrite factory
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(dwrite_factory), reinterpret_cast<IUnknown **>(dwrite_factory.put()))))
    {
        Logger::LogF("[Error] Failed to create DWrite factory");
        return;
    }
    wic_factory = winrt::create_instance<IWICImagingFactory2>(CLSID_WICImagingFactory2);

    // dx11 device, context
    UINT creation_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(ENABLE_DEBUG_LAYER)
    creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
                                          D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1};
    D3D_FEATURE_LEVEL feature_level;

    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11DeviceContext> context;
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creation_flags, feature_levels, ARRAYSIZE(feature_levels), D3D11_SDK_VERSION,
                                 device.put(), &feature_level, context.put())))
    {
        Logger::LogF("[Error] Failed to create device and context");
        return;
    }
    d3d_device = device.as<ID3D11Device3>();
    d3d_context = context.as<ID3D11DeviceContext3>();

    // swapchain
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

    winrt::com_ptr<IDXGIDevice3> dxgi_device = d3d_device.as<IDXGIDevice3>();

    // dxgi adapter
    winrt::com_ptr<IDXGIAdapter> dxgi_adapter;
    if (FAILED(dxgi_device->GetAdapter(dxgi_adapter.put())))
    {
        Logger::LogF("[Error] Failed to get DXGI adapter");
        return;
    };
    winrt::com_ptr<IDXGIFactory2> dxgi_factory;
    if (FAILED(dxgi_adapter->GetParent(IID_PPV_ARGS(dxgi_factory.put()))))
    {
        Logger::LogF("[Error] Failed to get DXGI factory");
        return;
    }
    if (Logger::ErrorF(dxgi_factory->CreateSwapChainForCoreWindow(d3d_device.get(), winrt::get_unknown(CoreApplication::MainView().CoreWindow()),
                                                                  &swapchain_desc, nullptr, swapchain.put()),
                       "[Error] Failed to create swapchain"))
    {
        return;
    }

    if (FAILED(dxgi_device->SetMaximumFrameLatency(1)))
    {
        Logger::LogF("[Error] Failed to set maximum frame latency");
        return;
    };

    // d2d device and context
    if (FAILED(d2d_factory->CreateDevice(dxgi_device.get(), d2d_device.put())))
    {
        Logger::LogF("[Error] Failed to create D2D device");
        return;
    }
    if (FAILED(d2d_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, d2d_context.put())))
    {
        Logger::LogF("[Error] Failed to create D2D context");
        return;
    }
}

void DxManager::CreateRenderTargetView()
{
    // Render Target
    winrt::com_ptr<ID3D11Texture2D> back_buffer;
    if (FAILED(swapchain->GetBuffer(0, IID_PPV_ARGS(back_buffer.put()))))
    {
        Logger::LogF("[Error] Failed to get back_buffer");
        return;
    }
    if (FAILED(d3d_device->CreateRenderTargetView(back_buffer.get(), nullptr, d3d_render_target_view.put())))
    {
        Logger::LogF("[Error] Failed to create render_target_view");
        return;
    };
    D3D11_TEXTURE2D_DESC back_buffer_desc = {};
    back_buffer->GetDesc(&back_buffer_desc);

    screen_viewport = CD3D11_VIEWPORT(0.0f, 0.0f, back_buffer_desc.Width, back_buffer_desc.Height);

    d3d_context->RSSetViewports(1, &screen_viewport);

    // direct2D bitmap creation stuff
    D2D1_BITMAP_PROPERTIES1 bitmapProperties =
        D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
                                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), dpi, dpi);

    winrt::com_ptr<IDXGIResource1> dxgi_back_buffer;
    if (FAILED(swapchain->GetBuffer(0, IID_PPV_ARGS(dxgi_back_buffer.put()))))
    {
        Logger::LogF("[Error] Failed to get back_buffer");
        return;
    }

    winrt::com_ptr<IDXGISurface2> dxgi_surface;
    if (FAILED(dxgi_back_buffer->CreateSubresourceSurface(0, dxgi_surface.put())))
    {
        Logger::LogF("[Error] Failed to create dxgi_surface");
        return;
    }

        if (FAILED(d2d_context->CreateBitmapFromDxgiSurface(dxgi_surface.get(), &bitmapProperties, d2d_target_bitmap.put())))
    {
        Logger::LogF("[Error] Failed to create d2d_target_bitmap");
        return;
    };

    d2d_context->SetTarget(d2d_target_bitmap.get());
    d2d_context->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

    resizing = false;
}

void DxManager::OnWindowResize(CoreWindow const &, WindowSizeChangedEventArgs const &args)
{
    resizing = true;

    d3d_context->OMSetRenderTargets(0, nullptr, nullptr);
    d3d_render_target_view = nullptr;
    d2d_context->SetTarget(nullptr);
    d2d_target_bitmap = nullptr;
    d3d_context->Flush();

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
