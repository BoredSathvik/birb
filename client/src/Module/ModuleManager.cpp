#include "ModuleManager.h"

void ModuleManager::InitModules()
{
    Modules.emplace_back(new Zoom());
    Modules.emplace_back(new Cps());
    Modules.emplace_back(new Fps());
}

std::vector<Module *> ModuleManager::getModules()
{
    return Modules;
}

Module *ModuleManager::getModuleByName(std::string name)
{
    for (auto mod : Modules)
    {
        if (mod->name == name)
        {
            return mod;
        }
    }
};