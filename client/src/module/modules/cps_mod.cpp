#include "cps_mod.h"

CPSMod::CPSMod() : Module("CPS Counter", "cps_mod", true)
{
}

CPSMod::~CPSMod()
{
}

void CPSMod::OnInit()
{
    last = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

void CPSMod::OnHUDRender()
{
    milliseconds now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    while ((now.count() - last.count()) > 100)
    {
        last = now + milliseconds(100);

        current = (current + 1) % 20;
        clicks[current] = 0;
    }

    if (this->IsEnabled())
    {
        bool show = true;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.0f, 15.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
        ImGui::SetNextWindowPos(ImVec2(Global::width - 200, Global::height - 100));
        ImGui::Begin("CPS Counter", &show,
                     ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoNav);
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(2);

        float sum = 0;
        for (int i = 0; i < 20; ++i)
        {
            sum += clicks[i];
        }

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
        ImGui::Text("CPS: %1.0f", sum / 2);
        ImGui::PopFont();
        ImGui::End();
    }
}

bool CPSMod::OnMouse(char button, char state, int x, int y)
{
    if (button == 1 && state == 0)
    {
        clicks[current]++;
    }

    return false;
}
