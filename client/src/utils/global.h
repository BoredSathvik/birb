#pragma once

#include <windows.h>

class Global {
   public:
    static inline HMODULE h_mod;
    static inline bool running = true;

    static inline int width = 0;
    static inline int height = 0;
};