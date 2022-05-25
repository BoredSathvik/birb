#pragma once

#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Core.h>

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::ApplicationModel::Core;

class UIThread
{
public:
    static winrt::Windows::Foundation::IAsyncAction RunOnUIThreadAsync(DispatchedHandler const &callback)
    {
        winrt::agile_ref<CoreWindow> window = CoreApplication::MainView().CoreWindow();

        return window.get().Dispatcher().RunAsync(CoreDispatcherPriority::Normal, callback);
    }
};