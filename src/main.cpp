// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <iostream>
#include <string>
#include <gtkmm.h>

// Tree model columns:
class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
    public:
    ModelColumns()
    {
        add(collumn_id);
        add(collumn_name);
        add(collumn_number);
        add(collumn_percentage);
    }

    Gtk::TreeModelColumn<unsigned int>  collumn_id;
    Gtk::TreeModelColumn<Glib::ustring> collumn_name;
    Gtk::TreeModelColumn<short>         collumn_number;
    Gtk::TreeModelColumn<int>           collumn_percentage;
};

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Signal handlers:
    void onNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    ModelColumns queue_tree_collumns;
    ModelColumns album_tree_collumns;
    ModelColumns playlist_tree_collumns;

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

    // Create the Tree model:
    queue_tree_refrence = Gtk::ListStore::create(queue_tree_collumns);
    queue_tree.set_model(queue_tree_refrence);

    // Fill the TreeView's model
    auto row                        = *(queue_tree_refrence->append());
    row[queue_tree_collumns.collumn_id]         = 1;
    row[queue_tree_collumns.collumn_name]       = "Billy Bob";
    row[queue_tree_collumns.collumn_number]     = 10;
    row[queue_tree_collumns.collumn_percentage] = 15;

    row                             = *(queue_tree_refrence->append());
    row[queue_tree_collumns.collumn_id]         = 2;
    row[queue_tree_collumns.collumn_name]       = "Joey Jojo";
    row[queue_tree_collumns.collumn_number]     = 20;
    row[queue_tree_collumns.collumn_percentage] = 40;

    row                             = *(queue_tree_refrence->append());
    row[queue_tree_collumns.collumn_id]         = 3;
    row[queue_tree_collumns.collumn_name]       = "Rob McRoberts";
    row[queue_tree_collumns.collumn_number]     = 30;
    row[queue_tree_collumns.collumn_percentage] = 70;

    // Add the TreeView's view columns:
    // This number will be shown with the default numeric formatting.
    queue_tree.append_column("Title", queue_tree_collumns.collumn_id);
    queue_tree.append_column("Album", queue_tree_collumns.collumn_name);

    queue_tree.append_column_numeric("Artist", queue_tree_collumns.collumn_number, "%010d" /* 10 digits, using leading zeroes. */);

    // Display a progress bar instead of a decimal number:
    auto cell       = Gtk::make_managed<Gtk::CellRendererProgress>();
    int  cols_count = queue_tree.append_column("Duration", *cell);
    auto pColumn    = queue_tree.get_column(cols_count - 1);
    if (pColumn)
    {
        pColumn->add_attribute(cell->property_value(), queue_tree_collumns.collumn_percentage);
    }

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