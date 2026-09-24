// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <vector>
#include <gtkmm.h>
#include "../../library/entries.h"
#include "../../library/library.h"
#include "../utils.h"

class Playlists
{
  public:
    Playlists();
    void update();

    std::vector<PlaylistEntry>   playlists = koji::library::getPlaylists();
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
  private:
    void on_clicked(int n_press, double x, double y);
};