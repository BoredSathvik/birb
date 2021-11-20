#pragma once

#include <vector>
#include "Module.h"

class ModuleManager
{

public:
    static inline std::vector<class Module *> *Modules = new std::vector<class Module *>();
    static void InitModules();
    static void AddModule(Module *Module);
    static void RemoveModules();
    static void RemoveModule(Module *Module);
};
