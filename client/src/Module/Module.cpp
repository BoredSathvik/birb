#include "Module.h"

Module::Module(std::string name)
{
    this->name = name;
    this->enabled = true;
}

Module::~Module()
{
    delete &this->name;
}

void Module::Toggle()
{
    this->enabled = !this->enabled;
}

void Module::onUIFrame(MinecraftUIRenderContext *renderCTX)
{
}

bool Module::onKey(bool keyMap[254], int key, bool pressed)
{
    return true;
}