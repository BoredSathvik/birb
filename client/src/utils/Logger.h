#pragma once

#include <string>
#include <Windows.h>
#include <fstream>

class Logger
{
public:
    static void LogF(const char *out)
    {
        std::string dir = getenv("APPDATA") + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\" + std::string("Birb_Logs.txt"));

        CloseHandle(CreateFileA(dir.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

        std::ofstream logs;
        logs.open(dir.c_str(), std::ios_base::app);
        logs << out << std::endl;
        logs.close();
    }
    static void LogF(const std::string out)
    {
        Logger::LogF(out.c_str());
    }

    static bool ErrorF(const HRESULT hr, const char *out)
    {
        if (FAILED(hr))
        {
            std::string out_str = std::string(out);
            out_str.push_back(' ');
            out_str.append(std::to_string(hr));

            Logger::LogF(out_str);
            return true;
        }

        return false;
    }
};