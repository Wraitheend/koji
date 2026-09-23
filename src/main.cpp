// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <gtkmm.h>
#include "library/entries.h"
#include "library/library.h"

std::string formatTime(const float seconds)
{
    if (seconds < 0.0f)
        return "--:--";

    int total   = static_cast<int>(seconds);
    int hours   = total / 3600;
    int minutes = (total % 3600) / 60;
    int secs    = total % 60;

    if (hours > 0)
        return std::format("{:02}:{:02}:{:02}", hours, minutes, secs);
    return std::format("{:02}:{:02}", minutes, secs);
}

// Tree model columns:
class TreeColumnSet : public Gtk::TreeModel::ColumnRecord
{
  public:
    std::deque<Gtk::TreeModelColumn<Glib::ustring>> string_columns;

    Gtk::TreeModelColumn<Glib::ustring> &addStringColumn()
    {
        string_columns.emplace_back();
        Gtk::TreeModelColumn<Glib::ustring> &new_column = string_columns.back();
        add(new_column);
        return new_column;
    }
};

Glib::RefPtr<Gtk::ListStore> setupStringTreeView(Gtk::TreeView &tree_view, TreeColumnSet &column_set, const std::vector<Glib::ustring> &column_headers)
{
    for (unsigned int header_index = 0; header_index < column_headers.size(); ++header_index)
    {
        column_set.addStringColumn();
    }

    Glib::RefPtr<Gtk::ListStore> list_store_reference = Gtk::ListStore::create(column_set);
    tree_view.set_model(list_store_reference);

    for (unsigned int header_index = 0; header_index < column_headers.size(); ++header_index)
    {
        tree_view.append_column(column_headers[header_index], column_set.string_columns[header_index]);
    }

    return list_store_reference;
}

class Queue
{
  public:
    Queue();

    TreeColumnSet                collumns;
    Gtk::Box                     box;
    Gtk::ScrolledWindow          window;
    Gtk::TreeView                tree;
    Glib::RefPtr<Gtk::ListStore> tree_refrence;
};

Queue::Queue()
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

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Signal handlers:
    void onNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    // Main
    Gtk::Notebook tabbar_notebook;

    Queue queue;

    // Album
    TreeColumnSet                album_collumns;
    Gtk::Box                     album_tab_box;
    Gtk::ScrolledWindow          album_window;
    Gtk::TreeView                album_tree;
    Glib::RefPtr<Gtk::ListStore> album_tree_refrence;

    // Playlist
    TreeColumnSet                playlist_collumns;
    Gtk::Box                     playlist_tab_box;
    Gtk::ScrolledWindow          playlist_window;
    Gtk::TreeView                playlist_tree;
    Glib::RefPtr<Gtk::ListStore> playlist_tree_refrence;
};

Window::Window()
{
    set_title("Koji");
    set_default_size(1920, 1080);
    set_child(tabbar_notebook);

    // Add the TreeView, inside a ScrolledWindow, with the button underneath:

    // Add the Notebook pages:
    tabbar_notebook.append_page(queue.box, "Queue");
    tabbar_notebook.append_page(album_tab_box, "Albums");
    tabbar_notebook.append_page(playlist_tab_box, "Playlists");

    tabbar_notebook.signal_switch_page().connect(sigc::mem_fun(*this, &Window::onNotebookSwitchPage));
}

Window::~Window() {}

void Window::onNotebookSwitchPage(Gtk::Widget * /* page */, guint page_num)
{
    std::cout << "Switched to tab with index " << page_num << std::endl;

    // You can also use tabbar_notebook.get_current_page() to get this index.
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("cc.silverfiles.koji");

    // Shows the window and returns when it is closed.
    return app->make_window_and_run<Window>(argc, argv);
}