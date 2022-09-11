#pragma once

#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <winrt/windows.foundation.h>
#include <winrt/windows.networking.sockets.h>

#include <sstream>
#include <string>

#include "../../utils/global.h"
#include "../../utils/logger.h"
#include "../../utils/ui_thread.h"
#include "../module.h"

using namespace winrt;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Web::Http;
using namespace winrt::Windows::Networking::Sockets;

class TestMod : public Module {
   public:
    TestMod();
    ~TestMod();

   private:
    void OnInit() override;
};