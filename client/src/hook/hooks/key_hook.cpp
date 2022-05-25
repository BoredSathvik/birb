#include "./key_hook.h"

KeyHook::KeyHook() : Hook(std::string("key_hook"), std::string("48 ?? ?? ?? 0F B6 ?? 4C ?? ?? ?? ?? ?? ?? 89 ?? ?? ?? 88")) {}

void KeyHook::HookFunc()
{
    this->AutoHook(KeyHookCallBack, &func_original);
}

void KeyHook::KeyHookCallBack(int key, int state)
{
    auto io = ImGui::GetIO();

    if (!io.WantCaptureKeyboard)
        return PLH::FnCast(func_original, KeyHookCallBack)(key, state);
}