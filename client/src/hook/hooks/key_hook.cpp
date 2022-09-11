#include "./key_hook.h"

#include "../../gui/gui.h"
#include "../../module/module_manager.h"

KeyHook::KeyHook() : Hook(std::string("key_hook"), std::string("48 ?? ?? ?? 0F B6 ?? 4C ?? ?? ?? ?? ?? ?? 89 ?? ?? ?? 88")) {}

void KeyHook::HookFunc() { this->AutoHook(KeyHookCallback, &func_original); }

void KeyHook::KeyHookCallback(int key, int state) {
    // Sets the key state
    keys[key] = state;

    bool block = false;

    block = Gui::GetInstance()->OnKey(key, state, keys) || block;

    for (auto mod : *ModuleManager::GetInstance()->modules) {
        block = mod->OnKey(key, state, keys) || block;
    }

    if (!block) return PLH::FnCast(func_original, KeyHookCallback)(key, state);
}