#pragma once

#include <Windows.h>
#include <fstream>
#include <string>

#include "../Module/ModuleManager.h"
#include "../Hook/HookManager.h"

class Utils
{
public:
    static inline HMODULE hMod;
    static inline bool keys[254];

    static void UnInject();

    static void DebugF(const char *out);
    static void DebugF(const std::string out);
};