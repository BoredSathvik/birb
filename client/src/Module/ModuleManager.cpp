#include "ModuleManager.h"
#include "Modules/UnInject.h"

void ModuleManager::InitModules()
{
    ModuleManager::AddModule(new UnInject());
}

void ModuleManager::AddModule(Module *Module)
{
    Utils::DebugF(std::string("Successfully loaded " + Module->name + " module"));
    ModuleManager::Modules->push_back(Module);
}

void ModuleManager::RemoveModules()
{
    for (auto Module : *ModuleManager::Modules)
    {
        ModuleManager::RemoveModule(Module);
    }

    ModuleManager::Modules->clear();
    delete ModuleManager::Modules;
}

void ModuleManager::RemoveModule(Module *Module)
{
    delete Module;
}