// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <iterator>
#include <string>
#include <vector>
#include <clocale>

#include "../library/entries.h"

#include "utils.h"
#include "components.h"

using namespace std;

bool Player::init()
{
    setlocale(LC_NUMERIC, "C");
    
    mpv_context = mpv_create();

    if (!mpv_context)
    {
        std::cout << "Error creating mpv context" << std::endl;
        cleanup();
        return false;
    }

    if (mpv_initialize(mpv_context) != 0)
    {
        std::cout << "Error initializing mpv context" << std::endl;
        cleanup();
        return false;
    }

    mpv_set_option_string(mpv_context, "vo", "null");
    mpv_set_option_string(mpv_context, "audio-format", "s16le");
    mpv_set_property_string(mpv_context, "volume", to_string(volume).c_str());
    return true;
}

void Player::cleanup()
{
    mpv_destroy(mpv_context);
}


void Player::togglePause() 
{
    paused = !paused;

    if (paused)
        mpv_set_property_string(mpv_context, "pause", "yes");
    else
        mpv_set_property_string(mpv_context, "pause", "no");
}

void Player::toggleRepeat() 
{
    if (repeat_mode == RepeatMode::Off)
    {
        repeat_mode = RepeatMode::All;
    }
    else if (repeat_mode == RepeatMode::All)
    {
        repeat_mode = RepeatMode::Track;
    }
    else if (repeat_mode == RepeatMode::Track)
    {
        repeat_mode = RepeatMode::Off;
    }
}

void Player::toggleShuffle() 
{
    shuffle = !shuffle;

    if (shuffle)
    {
        queue.unshuffled_queue = queue.queue;
        random_engine.seed(random_device{}());
        ranges::shuffle(queue.queue, random_engine);
    }
    else
    {
        queue.queue = queue.unshuffled_queue;
        queue.unshuffled_queue.clear();
    }
}

void Player::stopPlayback()
{
    current_song = -1;
    paused       = true;
    mpv_command_string(mpv_context, "stop");
    mpv_set_property_string(mpv_context, "pause", "yes");
}

// void updateCurrentSong(PlayerContext &player_context)
// {
//     player_context.paused = false;
//     updatePause(player_context);
//     const char *play_command[] = {"loadfile", player_context.current_song.path.c_str(), "replace", nullptr};
//     mpv_command(player_context.mpv_context, play_command);
// }


// void updateVolume(PlayerContext &player_context, const int level = 0)
// {
//     player_context.volume += level;
//     mpv_set_property_string(player_context.mpv_context, "volume", to_string(player_context.volume).c_str());
// }

// void addSongsToQueue(PlayerContext &player_context, vector<SongEntry> &songs)
// {
//     if (player_context.shuffle)
//     {
//         player_context.unshuffled_queue.insert(player_context.unshuffled_queue.end(), songs.begin(), songs.end());
//         ranges::shuffle(songs, player_context.random_engine);
//     }

//     if (player_context.queue.empty())
//     {
//         player_context.current_song = songs[0];
//         updateCurrentSong(player_context);
//     }

//     player_context.queue.insert(player_context.queue.end(), songs.begin(), songs.end());
// }



// void cycleSong(PlayerContext& player_context)
// {
//     PlayerContext &context = player_context;
//     vector<SongEntry> &queue = context.queue;

//     vector<SongEntry>::const_iterator iterator = std::find(queue.cbegin(), queue.cend(), context.current_song);

//     if (iterator == queue.cend())
//         stopSong(player_context);
//     else
//     {
//         const int song_index = distance(player_context.queue.cbegin(), iterator) + 1;

//         if (player_context.repeat_mode == RepeatMode::Track)
//             updateCurrentSong(player_context);
//         else if (song_index >= queue.size() && context.repeat_mode == RepeatMode::All)
//             context.current_song = queue.front();
//         else if (song_index >= queue.size())
//             stopSong(player_context);
//         else
//             context.current_song = queue[song_index];
//     }

//     updateCurrentSong(player_context);
// }

// bool songCycle(PlayerContext &player_context)
// {
//     if (player_context.current_song == SongEntry{})
//         return true;

//     double time_remaining;
//     mpv_get_property(player_context.mpv_context, "time-pos", MPV_FORMAT_DOUBLE, &time_remaining);
//     player_context.position_seconds = static_cast<float>(time_remaining);

//     mpv_event *event = mpv_wait_event(player_context.mpv_context, 0);

//     if (event->event_id == MPV_EVENT_END_FILE)
//     {
//         mpv_event_end_file *end_file = static_cast<mpv_event_end_file *>(event->data);

//         if (end_file->reason == MPV_END_FILE_REASON_EOF)
//             cycleSong(player_context);   
//     }

//     return true;
// }

// bool keyCycle(PlayerContext &player_context)
// {
//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Q))
//         return false;

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_X))
//         stopSong(player_context);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Space))
//         togglePause(player_context);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_S))
//         toggleShuffle(player_context);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_R))
//         toggleRepeatMode(player_context.repeat_mode);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Minus) && player_context.volume - 5 >= 0)
//         updateVolume(player_context, -5);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Equal) && player_context.volume + 5 <= 100)
//         updateVolume(player_context, 5);

//     return true;
// }

// bool pollEvents(PlayerContext &player_context)
// {
//     if (!songCycle(player_context))
//         return false;

//     if (!keyCycle(player_context))
//         return false;

//     return true;
// }

