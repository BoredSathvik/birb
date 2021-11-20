#include "Keyboard.h"

void __fastcall Keyboard::KeyboardCB(int key, bool pressed)
{

    Utils::keys[key] = pressed;

    bool ret = true;

    for (auto Module : *ModuleManager::Modules)
    {
        if (Module->onKey(Utils::keys, key, pressed) == false)
        {
            ret = false;
        };
    }
    if (ret)
    {
        PLH::FnCast(KeyboardOG, KeyboardCB)(key, pressed);
    }
}

Keyboard::Keyboard() : Hook::Hook("Keyboard", "48 89 5C 24 ?? 57 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA") {}

Keyboard::~Keyboard()
{
}

bool Keyboard::run()
{
    return this->hookFn(KeyboardCB, &KeyboardOG);
}