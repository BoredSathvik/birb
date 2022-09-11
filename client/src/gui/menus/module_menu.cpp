#include "module_menu.h"

void ModuleMenu::Render() {
    ScrollBar(20);

    ImGuiStyle &style = ImGui::GetStyle();
    ImVec2 module_size(200, 200);
    float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(40.0f, 40.0f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.25f, 0.25f, 0.25f, 0.80f));

    for (int i = 0; i < ModuleManager::GetInstance()->modules->size(); i++) {
        ImGui::PushID(i);

        RenderModule(i);

        float last_button_x2 = ImGui::GetItemRectMax().x;
        float next_button_x2 = last_button_x2 + style.ItemSpacing.x + module_size.x;  // Expected position if next button was on same line
        if (i + 1 < ModuleManager::GetInstance()->modules->size() && next_button_x2 < window_visible_x2) ImGui::SameLine();

        ImGui::PopID();
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

void ModuleMenu::ScrollBar(float offset) {
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

void ModuleMenu::RenderModule(int index) {
    auto mod = (*ModuleManager::GetInstance()->modules)[index];

    auto current_draw_list = ImGui::GetWindowDrawList();

    ImGui::BeginChild("Module", ImVec2(200, 200));

    ImGui::SetCursorPos(
        ImVec2(((ImGui::GetWindowWidth() / 2) - ((ImGui::GetFontSize() * mod->GetName().length()) / 4)), ImGui::GetWindowHeight() - 90));
    ImGui::Text(mod->GetName().c_str());

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 50);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    if (ImGui::Button(mod->IsEnabled() ? "Enabled" : "Disabled", ImVec2(140, 50))) {
        mod->Toggle();
    }
    ImGui::PopStyleColor(3);

    ImColor button_color = mod->IsEnabled() ? ImColor(0.05f, 0.75f, 0.05f, 0.80f) : ImColor(0.75f, 0.05f, 0.05f, 0.80f);

    if (ImGui::IsItemActive())
        button_color = mod->IsEnabled() ? ImColor(0.0f, 0.70f, 0.0f, 0.80f) : ImColor(0.70f, 0.0f, 0.0f, 0.80f);
    else if (ImGui::IsItemHovered())
        button_color = mod->IsEnabled() ? ImColor(0.05f, 0.85f, 0.05f, 0.80f) : ImColor(0.85f, 0.05f, 0.05f, 0.80f);

    current_draw_list->AddRectFilled(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
                                     ImVec2(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y), button_color, 10.0f,
                                     ImDrawFlags_RoundCornersBottomLeft);

    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 140, ImGui::GetWindowHeight() - 50));

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
    if (ImGui::Button(ICON_MD_SETTINGS, ImVec2(60, 50))) {
        SettingsPopup(mod);
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    button_color = ImColor(0.35f, 0.35f, 0.35f, 0.80f);

    if (ImGui::IsItemActive())
        button_color = ImColor(0.25f, 0.25f, 0.25f, 0.80f);
    else if (ImGui::IsItemHovered())
        button_color = ImColor(0.45f, 0.45f, 0.45f, 0.80f);

    current_draw_list->AddRectFilled(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
                                     ImVec2(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y), button_color, 10.0f,
                                     ImDrawFlags_RoundCornersBottomRight);

    ImGui::EndChild();
}

void ModuleMenu::SettingsPopup(Module *mod) {}