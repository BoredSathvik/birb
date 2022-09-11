#pragma once

#include <functional>
#include <string>

#include "../hook/hooks/key_hook.h"
#include "../hook/hooks/mouse_hook.h"

class Module {
   private:
    std::string id;
    std::string name;
    bool hidden;
    bool enabled;

   public:
    Module(std::string name, std::string id, bool enabled = true, bool hidden = false);
    virtual ~Module();

    void Init() { this->OnInit(); };

    std::string GetName() { return this->name; };
    std::string GetId() { return this->id; };
    bool IsEnabled() { return this->enabled; };

    void Toggle();

    virtual void OnInit(){};
    virtual void OnToggle(){};

    virtual bool OnKey(char key, bool state, bool keys[256]) { return false; };
    virtual bool OnMouse(char button, char state, int x, int y) { return false; };

    virtual void OnHUDRender(){};
};