#include "console_menu.h"

void ConsoleMenu::Render() { ScrollBar(20); }

void ConsoleMenu::ScrollBar(float offset) {
    auto style = ImGui::GetStyle();
    ImGuiWindow *window = ImGui::GetCurrentWindow();

    const ImGuiID id = ImGui::GetWindowScrollbarID(window, ImGuiAxis_Y);
    ImGui::KeepAliveID(id);

    ImRect bb = ImGui::GetWindowScrollbarRect(window, ImGuiAxis_Y);
    bb.Min.x -= offset + style.ScrollbarSize;
    bb.Min.y += 20;
    bb.Max.x -= offset;
    bb.Max.y -= 20;

    float size_avail = window->InnerRect.Max[ImGuiAxis_Y] - window->InnerRect.Min[ImGuiAxis_Y];
    float size_contents = window->ContentSize[ImGuiAxis_Y] + window->WindowPadding[ImGuiAxis_Y] * 2.0f;
    ImS64 scroll = (ImS64)window->Scroll[ImGuiAxis_Y];
    ImGui::ScrollbarEx(bb, id, ImGuiAxis_Y, &scroll, (ImS64)size_avail, (ImS64)size_contents, ImDrawFlags_RoundCornersAll);
    window->Scroll[ImGuiAxis_Y] = (float)scroll;
}
