// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <vector>
#include <gtkmm.h>
#include "../../library/entries.h"
#include "../utils.h"

class Queue
{
  public:
    Queue();
    void updateView();

    std::vector<SongEntry>       queue;
    std::vector<SongEntry>       unshuffled_queue;
    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
   Glib::RefPtr<Gtk::ListStore> tree_refrence;
  private:
    void on_selection_changed();
};