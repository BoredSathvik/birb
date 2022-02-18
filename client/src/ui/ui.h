#pragma once

#include <windows.h>
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>

#include <d3d11_3.h>
#include <dxgi1_6.h>

#include "../utils/logger.h"

using namespace winrt::Windows::ApplicationModel::Core;

class Ui
{
    winrt::com_ptr<ID3D11Device3> m_d3dDevice;
    winrt::com_ptr<ID3D11DeviceContext3> m_d3dContext;
    winrt::com_ptr<IDXGISwapChain1> m_swapChain;

    winrt::com_ptr<ID3D11RenderTargetView> m_renderTargetView;

    void InitializeD3D();
};
