#include "Module.h"

Module::Module(std::string name, std::string id, bool enabled, bool hidden) {
    this->name = name;
    this->id = id;
    this->enabled = enabled;
    this->hidden = hidden;
}

Module::~Module() {}

void Module::Toggle() {
    this->enabled = !this->enabled;

    this->OnToggle();
}
