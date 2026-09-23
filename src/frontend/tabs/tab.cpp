// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 silver_gray
#include "imgui.h"
#include "tabs.h"

using namespace koji::backend::app;

namespace koji::frontend::tabs::internal
{
bool beginTab(const char *label, AppState &state)
{
    if (!ImGui::BeginTabItem(label, nullptr, ImGuiTabItemFlags_NoArrowNav))
        return false;

    // state.display_content_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    // int scaled_width            = (int)(state.width * state.display_content_scale) * 2;
    // int scaled_height           = (int)(state.height * state.display_content_scale) * 2;
    ImGui::Spacing();
    ImGui::BeginChild("tabFrame", ImVec2(0, -125), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_NoNavFocus);
    ImGui::PushItemFlag(ImGuiItemFlags_NoTabStop, true);
    ImGui::Separator();

    return true;
}

void endTab()
{
    ImGui::PopItemFlag();
    ImGui::EndChild();
    ImGui::EndTabItem();
}
} // namespace koji::frontend::tabs::internal
