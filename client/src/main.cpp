#include <windows.h>
#pragma comment(lib, "windowsapp")
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>

#include <d3d11_3.h>
#include <dxgi1_6.h>

#include "utils/logger.h"

using namespace winrt::Windows::ApplicationModel::Core;

void start()
{
    Logger::LogF("Starting...");

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
    }
    Logger::LogF("Successfully created D3D11 Device and Context");

    winrt::com_ptr<ID3D11Device3> d3dDevice = device.as<ID3D11Device3>();
    winrt::com_ptr<ID3D11DeviceContext3> d3dContext = context.as<ID3D11DeviceContext3>();

    winrt::com_ptr<IDXGIDevice3> dxgiDevice;
    dxgiDevice = d3dDevice.as<IDXGIDevice3>();

    winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
    if (FAILED(dxgiDevice->GetAdapter(dxgiAdapter.put())))
    {
        Logger::LogF("[Error] Failed to get DXGI adapter");
    };
    Logger::LogF("Successfully got DXGI adapter");

    winrt::com_ptr<IDXGIFactory2> dxgiFactory;
    if (FAILED(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.put()))))
    {
        Logger::LogF("[Error] Failed to get DXGI factory");
    }
    Logger::LogF("Successfully got DXGI factory");

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

    winrt::com_ptr<IDXGISwapChain1> swapChain;
    if (FAILED(dxgiFactory->CreateSwapChainForCoreWindow(
            d3dDevice.get(),
            winrt::get_unknown(CoreApplication::MainView().CoreWindow()),
            &swapChainDesc,
            nullptr,
            swapChain.put())))
    {

        Logger::LogF("[Error] Failed to create swapchain");
    }
    Logger::LogF("Successfully created swapchain");

    // winrt::com_ptr<ID3D11Texture2D1>
    //     backBuffer;
    // swapChain->GetBuffer(
    //     0,
    //     IID_PPV_ARGS(backBuffer.put()));

    // winrt::com_ptr<ID3D11RenderTargetView> renderTargetView;
    // d3dDevice->CreateRenderTargetView(
    //     backBuffer.get(),
    //     nullptr,
    //     renderTargetView.put());

    // D3D11_TEXTURE2D_DESC backBufferDesc = {0};
    // backBuffer->GetDesc(&backBufferDesc);

    // CD3D11_VIEWPORT viewport(
    //     0.0f,
    //     0.0f,
    //     static_cast<float>(backBufferDesc.Width),
    //     static_cast<float>(backBufferDesc.Height));

    // d3dContext->RSSetViewports(1, &viewport);
}

BOOL __stdcall DllMain(void *, int reason, void *)
{
    if (reason == 1)
    {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, NULL, 0, NULL);
    }
    else if (reason == 0)
    {
    }
    return true;
}
