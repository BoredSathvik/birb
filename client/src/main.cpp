#include <Windows.h>
#include <dxgi.h>
#include <d3d12.h>

void start()
{
    HMODULE libD3D12 = GetModuleHandle(L"d3d12.dll");
    HMODULE libDXGI = GetModuleHandle(L"dxgi.dll");
    void *CreateDXGIFactory = GetProcAddress(libDXGI, "CreateDXGIFactory");
    IDXGIFactory *factory;
    if ((((long(__stdcall *)(const IID &, void **))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void **)&factory)) > 0)
    {
    }
}

BOOL __stdcall DllMain(HMODULE hModule, int reason, void *)
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
