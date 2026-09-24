// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray

#include "queue.h"
#include <iostream>

Queue::Queue()
{
    window.set_child(tree);
    tree.set_enable_search(false);
    tree.set_rubber_banding(false);

    // Only show the scrollbars when they are necessary:
    window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    window.set_expand();

    box.append(window);

    std::vector<Glib::ustring> queue_column_headers = {"Title", "Album", "Artist", "Duration"};
    tree_refrence                                   = setupStringTreeView(tree, collumns, queue_column_headers);

    // for (int i = 0; i < static_cast<int>(songs.size()); ++i)
    Glib::RefPtr<Gtk::TreeSelection> selection = tree.get_selection();
    selection->signal_changed().connect(sigc::mem_fun(*this, &Queue::on_selection_changed));
}

void Queue::update()
{
    if (!(tree_refrence->children().size() == 0))
        tree_refrence->clear();
    for (SongEntry &song : queue)
    {
        auto row                        = *(tree_refrence->append());
        row[collumns.string_columns[0]] = song.title;
        row[collumns.string_columns[1]] = song.album;
        row[collumns.string_columns[2]] = song.artist;
        row[collumns.string_columns[3]] = formatTime(song.duration);
    }
}

void Queue::on_selection_changed()
{
    Gtk::TreeModel::iterator iter = tree.get_selection()->get_selected();

    if (!iter)
        return;

    Gtk::TreeModel::Row row = *iter;
    Glib::ustring title = row[collumns.string_columns[0]];

    std::cout << "Selected: " << title << std::endl;
}