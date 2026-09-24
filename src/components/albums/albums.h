// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <vector>
#include <gtkmm.h>
#include "../../library/entries.h"
#include "../../library/library.h"
#include "../utils.h"
#include "../queue/queue.h"

class Albums
{
  public:
    Albums();
    void update();
    void setQueue(Queue *queue_ptr) { queue = queue_ptr; }

    std::vector<AlbumEntry>      albums = koji::library::getAlbums();
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
  private:
    Queue *queue;
    void on_clicked(int n_press, double x, double y);
};