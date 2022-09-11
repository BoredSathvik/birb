#pragma once

#include <vector>

#include "module.h"
#include "modules/cps_mod.h"
#include "modules/test_mod.h"

class ModuleManager {
   private:
    ModuleManager();
    ~ModuleManager();

   public:
    std::vector<Module *> *modules;

    static ModuleManager *GetInstance() {
        static ModuleManager instance;
        return &instance;
    };

    void Init();
    void CleanModules();

    template <typename T>
    T *GetModule(char *name);
};