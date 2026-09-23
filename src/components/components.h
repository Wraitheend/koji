// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <vector>
#include <random>
#include <gtkmm.h>
#include <mpv/client.h>
#include "utils.h"
#include "../library/entries.h"
#include "../library/library.h"

enum class RepeatMode
{
    Off,
    All,
    Track
};

class Queue
{
  public:
    Queue();

    std::vector<SongEntry>       queue;
    std::vector<SongEntry>       unshuffled_queue;
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
};

class Albums
{
  public:
    Albums();

    std::vector<AlbumEntry>      albums = koji::library::getAlbums();
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
};

class Playlists
{
  public:
    Playlists();

    std::vector<PlaylistEntry>   playlists = koji::library::getPlaylists();
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
};

class Player
{
  public:
    bool init();
    void cleanup();
    
    void togglePause();
    void toggleRepeat();
    void toggleShuffle();

    void stopPlayback();

    int volume = 35;
    bool paused = false;
    bool shuffle = false;
    float position = 0.0f; // in seconds
    
    Queue     queue;
    Albums    albums;
    Playlists playlists;

    RepeatMode repeat_mode = RepeatMode::All;

    int current_song;
    std::mt19937 random_engine{std::random_device{}()};
    mpv_handle  *mpv_context = nullptr;
};
