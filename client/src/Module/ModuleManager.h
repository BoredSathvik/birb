#pragma once

#include <vector>
#include "Module.h"
#include "Modules/Cps.h"
#include "Modules/Fps.h"
#include "Modules/Zoom.h"

class ModuleManager
{
    static inline std::vector<Module *> Modules;

public:
    static void InitModules();
    static std::vector<Module *> getModules();
    static Module *getModuleByName(std::string name);
};