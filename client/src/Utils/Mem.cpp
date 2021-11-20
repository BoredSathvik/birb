#include "Mem.h"
#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t Mem::AOBScan(const char *pattern)
{

    MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandleA("Minecraft.Windows.exe"), &info, sizeof(MODULEINFO));

    MEMORY_BASIC_INFORMATION mbi{0};
    uintptr_t protectFlags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

    uintptr_t firstMatch = 0;
    auto start = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
    auto end = (uintptr_t)(start + info.SizeOfImage);
    auto pat = pattern;

    BYTE patByte = getByte(pat);
    const char *oldPat = pat;

    for (uintptr_t i = start; i < end; i++)
    {
        if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi)))
        {
            if (mbi.Protect & protectFlags || !(mbi.State & MEM_COMMIT))
            {
                i += mbi.RegionSize;
                continue;
            }
            for (uintptr_t j = (uintptr_t)mbi.BaseAddress; j < (uintptr_t)mbi.BaseAddress + mbi.RegionSize; j++)
            {
                if (!*pat)
                    return firstMatch;
                if (*(PBYTE)pat == '\?' || *(BYTE *)j == getByte(pat))
                {
                    if (!firstMatch)
                        firstMatch = j;
                    if (!pat[2])
                        return firstMatch;
                    if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                        pat += 3;
                    else
                        pat += 2;
                }
                else
                {
                    pat = pattern;
                    firstMatch = 0;
                }
            }
        }
    }
    return 0;
}

uintptr_t Mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;

    for (int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t *)addr;
        addr += offsets[i];
    }
    return addr;
}

HMODULE Mem::GetThisModule()
{
    return GetModuleHandleA(nullptr);
}