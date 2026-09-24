// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <vector>
#include <gtkmm.h>
#include "../../library/entries.h"
#include "../../library/library.h"
#include "../utils.h"

class Albums
{
  public:
    Albums();
    void update();

    std::vector<AlbumEntry>      albums = koji::library::getAlbums();
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
  private:
    void on_selection_changed();
};