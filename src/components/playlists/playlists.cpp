// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray

#include "playlists.h"
#include <iostream>

Playlists::Playlists()
{
    window.set_child(tree);
    tree.set_enable_search(false);

    // Only show the scrollbars when they are necessary:
    window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    window.set_expand();

    box.append(window);

    std::vector<Glib::ustring> queue_column_headers = {"Playlist"};
    tree_refrence                                   = setupStringTreeView(tree, collumns, queue_column_headers);

    update();
    
    Glib::RefPtr<Gtk::TreeSelection> selection = tree.get_selection();
    selection->signal_changed().connect(sigc::mem_fun(*this, &Playlists::on_selection_changed));
}

void Playlists::update()
{
    if (!(tree_refrence->children().size() == 0))
        tree_refrence->clear();
    for (PlaylistEntry &playlist : playlists)
    {
        auto row                        = *(tree_refrence->append());
        row[collumns.string_columns[0]] = playlist.title;
    }
}

void Playlists::on_selection_changed()
{
    Gtk::TreeModel::iterator iter = tree.get_selection()->get_selected();

    if (!iter)
        return;

    Gtk::TreeModel::Row row = *iter;
    Glib::ustring title = row[collumns.string_columns[0]];

    std::cout << "Selected: " << title << std::endl;
}