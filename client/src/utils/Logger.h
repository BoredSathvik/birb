#pragma once

#include <string>
#include <Windows.h>
#include <fstream>

class Logger
{
    static void DebugF(const char *out)
    {
        std::string dir = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + std::string("Birb_Logs.txt"));

        CloseHandle(CreateFileA(dir.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

        std::ofstream logs;
        logs.open(dir.c_str(), std::ios_base::app);
        logs << out << std::endl;
        logs.close();
    }

    static void DebugF(const std::string out)
    {
        Logger::DebugF(out.c_str());
    }
};