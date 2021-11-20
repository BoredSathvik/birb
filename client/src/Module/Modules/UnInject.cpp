#include "UnInject.h"

UnInject::UnInject() : Module("Uninject")
{
}

UnInject::~UnInject()
{
}

bool UnInject::onKey(bool keyMap[254], int key, bool pressed)
{
    if (keyMap[0x11] && keyMap[0x10] && keyMap['I']) // key = /
    {
        Utils::UnInject();
        return false;
    }

    return true;
}