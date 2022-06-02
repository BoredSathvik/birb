#pragma once

#include <windows.h>
#include "logger.h"
#include <thread>

class Global
{
private:
    static void UnLoad(HMODULE h_module)
    {
        Logger::LogF("Freeing Library...");

        while (!should_exit)
        {
            Sleep(100);
        }

        FreeLibraryAndExitThread(h_module, 0);
    }

public:
    static inline HMODULE h_mod;
    static inline bool running = true;
    static inline bool should_exit = false;

    static void UnInject()
    {
        running = false;
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UnLoad, h_mod, 0, nullptr));

        Logger::LogF("Freeing Library...");
    }
};