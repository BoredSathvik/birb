#include "Module_manager.h"

ModuleManager::ModuleManager()
{
    modules = new std::vector<Module *>();

    modules->push_back(new CPSMod());
    modules->push_back(new TestMod());
}

ModuleManager::~ModuleManager()
{
}

void ModuleManager::Init()
{
    for (auto module : *modules)
    {
        module->Init();
    }
}

void ModuleManager::CleanModules()
{
    for (auto module : *modules)
    {
        delete module;
    }
    modules->clear();
    delete modules;
}

template <typename T>
T *ModuleManager::GetModule(char *name)
{
    for (auto module : *modules)
    {
        if (module->name == std::string(name))
        {
            return (T *)module;
        }
    };
}
