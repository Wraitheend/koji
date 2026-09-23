// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray

#include "albums.h"

Albums::Albums()
{
    window.set_child(tree);
    tree.set_enable_search(false);

    // Only show the scrollbars when they are necessary:
    window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    window.set_expand();

    box.append(window);

    std::vector<Glib::ustring> queue_column_headers = {"Artist", "Album"};
    tree_refrence                                   = setupStringTreeView(tree, collumns, queue_column_headers);

    // for (int i = 0; i < static_cast<int>(songs.size()); ++i)
    for (AlbumEntry &album : albums)
    {
        auto row                        = *(tree_refrence->append());
        row[collumns.string_columns[0]] = album.artist;
        row[collumns.string_columns[1]] = album.title;
    }
}