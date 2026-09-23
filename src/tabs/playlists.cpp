// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray

#include "tabs.h"
#include <vector>

Playlists::Playlists()
{
    window.set_child(tree);

    // Only show the scrollbars when they are necessary:
    window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    window.set_expand();

    box.append(window);

    std::vector<Glib::ustring> queue_column_headers = {"Title", "Album", "Artist", "Duration"};
    tree_refrence                                   = setupStringTreeView(tree, collumns, queue_column_headers);

    std::vector<AlbumEntry> albums = koji::library::getAlbums();
    std::vector<SongEntry>  songs  = koji::library::getAlbumSongs(albums[0]);

    // for (int i = 0; i < static_cast<int>(songs.size()); ++i)
    for (SongEntry &song : songs)
    {
        auto row                        = *(tree_refrence->append());
        row[collumns.string_columns[0]] = song.title;
        row[collumns.string_columns[1]] = song.album;
        row[collumns.string_columns[2]] = song.artist;
        row[collumns.string_columns[3]] = formatTime(song.duration);
    }
}