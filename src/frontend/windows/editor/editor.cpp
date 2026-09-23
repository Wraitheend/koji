// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 silver_gray

#include "editor.h"
#include <algorithm>
#include <tuple>
#include <vector>
#include <stdlib.h>
#include "../../../backend/app.h"
#include "../../../backend/library/entries.h"
#include "../../../backend/library/playlists.h"
#include "../../../frontend/compontents/notification.h"
#include "imgui.h"
#include "menus.h"
#include "misc/cpp/imgui_stdlib.h"

using namespace std;
using namespace koji::backend::app;
using namespace koji::backend::library;
using namespace koji::frontend::components::notification;

namespace koji::frontend::windows::editor
{

void editorWindow(AppState &state)
{
    const ImVec2 window_size = ImGui::GetWindowSize();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::Begin("Playlist Editor", &state.editor_context.edit_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove); // ImGuiChildFlags_NavFlattened,
    ImGui::PushItemFlag(ImGuiItemFlags_NoTabStop, true);
    ImGui::PushItemFlag(ImGuiItemFlags_NoArrowNav, true);

    if (state.editor_context.playlist == PlaylistEntry{})
        selectPlaylistMenu(state);
    else if (state.editor_context.mode == EditorMode::Edit)
        editPlaylistMenu(state);
    else if (state.editor_context.mode == EditorMode::Rename)
    {
        ImGui::Text("Renamed Playlist Name: ");
        ImGui::SameLine();
        ImGui::InputText("##rename", &state.editor_context.rename);
        if (ImGui::Button("Submit"))
        {
            if (!renamePlaylist(state.editor_context.playlist, state.editor_context.rename))
                setNotification(state, "Error Rename Playlist Already Exists");
            else
                state.player_context.playlists = getPlaylists();
            state.editor_context.edit_window = false;
        }
    }

    ImGui::PopItemFlag();
    ImGui::PopItemFlag();
    ImGui::End();

    if (!state.editor_context.edit_window)
        state.editor_context = EditorContext{};
}
} // namespace koji::frontend::windows::editor
