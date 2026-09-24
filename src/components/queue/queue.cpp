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
    auto click_gesture = Gtk::GestureClick::create();
    click_gesture->signal_pressed().connect(sigc::mem_fun(*this, &Queue::on_clicked));
    tree.add_controller(click_gesture);
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

void Queue::on_clicked(int n_press, double x, double y)
{
    Gtk::TreeModel::Path path;

    if (!tree.get_path_at_pos(static_cast<int>(x), static_cast<int>(y), path))
        return;

    Gtk::TreeModel::iterator iterator = tree_refrence->get_iter(path);

    if (!iterator)
        return;

    Gtk::TreeModel::Row row = *iterator;
    Glib::ustring title = row[collumns.string_columns[0]];

    std::cout << "Selected: " << title << std::endl;
}