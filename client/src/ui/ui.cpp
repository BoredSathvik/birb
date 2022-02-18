#include "ui.h"

void Ui::InitializeD3D()
{

    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1};

    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11DeviceContext> context;

    D3D_FEATURE_LEVEL featureLevel;

    if (FAILED(D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            creationFlags,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            device.put(),
            &featureLevel,
            context.put())))
    {
        Logger::LogF("[Error] Failed to create device");
        return;
    }

    m_d3dDevice = device.as<ID3D11Device3>();
    m_d3dContext = context.as<ID3D11DeviceContext3>();

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = 0;
    swapChainDesc.Height = 0;
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER;
    swapChainDesc.Scaling = DXGI_SCALING_NONE;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

    winrt::com_ptr<IDXGIDevice3> dxgiDevice;
    dxgiDevice = m_d3dDevice.as<IDXGIDevice3>();

    winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
    if (FAILED(dxgiDevice->GetAdapter(dxgiAdapter.put())))
    {
        Logger::LogF("[Error] Failed to get DXGI adapter");
        return;
    };

    winrt::com_ptr<IDXGIFactory2> dxgiFactory;
    if (FAILED(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.put()))))
    {
        Logger::LogF("[Error] Failed to get DXGI factory");
        return;
    }
    if (FAILED(dxgiFactory->CreateSwapChainForCoreWindow(
            m_d3dDevice.get(),
            winrt::get_unknown(CoreApplication::MainView().CoreWindow()),
            &swapChainDesc,
            nullptr,
            m_swapChain.put())))
    {

        Logger::LogF("[Error] Failed to create swapchain");
        return;
    }

    winrt::com_ptr<ID3D11Texture2D> backBuffer;
    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.put()));
    m_d3dDevice->CreateRenderTargetView(backBuffer.get(), nullptr, m_renderTargetView.put());

    D3D11_TEXTURE2D_DESC backBufferDesc = {};
    backBuffer->GetDesc(&backBufferDesc);

    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = static_cast<float>(backBufferDesc.Width);
    viewport.Height = static_cast<float>(backBufferDesc.Height);
    viewport.MinDepth = D3D11_MIN_DEPTH;
    viewport.MaxDepth = D3D11_MAX_DEPTH;

    m_d3dContext->RSSetViewports(1, &viewport);

    // https://docs.microsoft.com/en-us/windows/uwp/gaming/setting-up-directx-resources
}