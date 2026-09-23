// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <iostream>
#include <string>
#include <gtkmm.h>

// Tree model columns:
class TreeColumnSet : public Gtk::TreeModel::ColumnRecord
{
public:
    std::deque<Gtk::TreeModelColumn<Glib::ustring>> string_columns;

    Gtk::TreeModelColumn<Glib::ustring>& add_string_column()
    {
        string_columns.emplace_back();
        Gtk::TreeModelColumn<Glib::ustring>& new_column = string_columns.back();
        add(new_column);
        return new_column;
    }
};

Glib::RefPtr<Gtk::ListStore> setup_string_tree_view(Gtk::TreeView& tree_view, TreeColumnSet& column_set, const std::vector<Glib::ustring>& column_headers)
{
    for (unsigned int header_index = 0; header_index < column_headers.size(); ++header_index)
    {
        column_set.add_string_column();
    }

    Glib::RefPtr<Gtk::ListStore> list_store_reference = Gtk::ListStore::create(column_set);
    tree_view.set_model(list_store_reference);

    for (unsigned int header_index = 0; header_index < column_headers.size(); ++header_index)
    {
        tree_view.append_column(column_headers[header_index], column_set.string_columns[header_index]);
    }

    return list_store_reference;
}

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Signal handlers:
    void onNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    TreeColumnSet queue_tree_collumns;
    TreeColumnSet album_tree_collumns;
    TreeColumnSet playlist_tree_collumns;

    // Child widgets:
    Gtk::Notebook tabbar_notebook;

    // Queue Child widgets:
    Gtk::Box queue_tab_box;
    Gtk::ScrolledWindow          queue_scrollable_window;
    Gtk::TreeView                queue_tree;
    Glib::RefPtr<Gtk::ListStore> queue_tree_refrence;
    
    // Album Child widgets:
    Gtk::Label album_label, playlist_label;

    // Playlist Child widgets:
};

Window::Window() // : queue_tab_box(Gtk::Orientation::VERTICAL), album_label("Contents of album tab"), playlist_label("Contents of playlist tab")
{
    set_title("Koji");
    set_default_size(1920, 1080);
    set_child(tabbar_notebook);

    // Add the TreeView, inside a ScrolledWindow, with the button underneath:
    // queue_scrollable_window.set_margin_top(5);
    queue_scrollable_window.set_child(queue_tree);

    // Only show the scrollbars when they are necessary:
    queue_scrollable_window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    queue_scrollable_window.set_expand();

    queue_tab_box.append(queue_scrollable_window);

    // Create the Tree model and view columns:
    std::vector<Glib::ustring> queue_column_headers = {"Title", "Album", "Artist", "Duration"};
    queue_tree_refrence = setup_string_tree_view(queue_tree, queue_tree_collumns, queue_column_headers);

    // Fill the TreeView's model
    auto row = *(queue_tree_refrence->append());
    row[queue_tree_collumns.string_columns[0]] = "1";
    row[queue_tree_collumns.string_columns[1]] = "Billy Bob";
    row[queue_tree_collumns.string_columns[2]] = "10";
    row[queue_tree_collumns.string_columns[3]] = "15";


    // Make all the columns reorderable:
    // This is not necessary, but it's nice to show the feature.
    // You can use TreeView::set_column_drag_function() to more
    // finely control column drag and drop.
    for (guint i = 0; i < 2; i++)
    {
        auto column = queue_tree.get_column(i);
        column->set_reorderable();
    }

    album_label.set_valign(Gtk::Align::START);
    playlist_label.set_valign(Gtk::Align::START);

    album_label.set_halign(Gtk::Align::START);
    playlist_label.set_halign(Gtk::Align::START);

    // Add the Notebook pages:
    tabbar_notebook.append_page(queue_tab_box, "Queue");
    tabbar_notebook.append_page(album_label, "Albums");
    tabbar_notebook.append_page(playlist_label, "Playlists");

    // for (int i = 0; i < 5; ++i) {
    //     auto button = Gtk::Button(Glib::ustring("Queue Item " + std::to_string(i)));

    //     // Optional: Connect signal
    //     // button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onButtonClick));

    //     button.set_valign(Gtk::Align::START);
    //     button.set_halign(Gtk::Align::START);

    //     queue_box.append(button);
    // }

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
    auto app = Gtk::Application::create("org.gtkmm.example");

    // Shows the window and returns when it is closed.
    return app->make_window_and_run<Window>(argc, argv);
}