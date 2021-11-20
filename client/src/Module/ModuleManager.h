#pragma once

#include <vector>
#include "Module.h"

class ModuleManager
{

public:
    static inline std::vector<Module *> *Modules = new std::vector<Module *>();
    static void InitModules();
    static void AddModule(Module *Module);
    static void RemoveModules();
    static void RemoveModule(Module *Module);
};
