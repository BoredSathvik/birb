#include <Windows.h>
#include <thread>

void start()
{
    //RenderFunction:
    // parm: __int64 a1, __int64 a2
    // ret: don't care
    // pattern: ?? 8B C4 ?? 89 58 18 55 56 57 ?? 54 ?? 55 ?? 56 ?? 57 ?? 8D A8 98 FD FF FF ?? 81 EC 30 03 00 00 ?? ?? 70 B8 0F ?? ?? A8 ?? 8B 05 71 82 0E 03
}

BOOL __stdcall DllMain(void *, int reason, void *)
{
    if (reason == 1)
    {
        std::thread(start).detach();
    }
    else if (reason == 0)
    {
    }
    return true;
}
