// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <iostream>
#include <string>
#include <gtkmm.h>

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Signal handlers:
    void onNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    // Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:
        ModelColumns()
        {
            add(m_col_id);
            add(m_col_name);
            add(m_col_number);
            add(m_col_percentage);
        }

        Gtk::TreeModelColumn<unsigned int>  m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<short>         m_col_number;
        Gtk::TreeModelColumn<int>           m_col_percentage;
    };

    ModelColumns m_Columns;

    // Child widgets:
    Gtk::Box queue_tab_box;

    Gtk::ScrolledWindow          m_ScrolledWindow;
    Gtk::TreeView                m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    // Child widgets:
    Gtk::Notebook tabbar_notebook;

    Gtk::Label album_label, playlist_label;
};

Window::Window() // : queue_tab_box(Gtk::Orientation::VERTICAL), album_label("Contents of album tab"), playlist_label("Contents of playlist tab")
{
    set_title("Koji");
    set_default_size(1920, 1080);
    set_child(tabbar_notebook);

    // set_child(queue_tab_box);

    // Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.set_child(m_TreeView);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    queue_tab_box.append(m_ScrolledWindow);

    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    // Fill the TreeView's model
    auto row                        = *(m_refTreeModel->append());
    row[m_Columns.m_col_id]         = 1;
    row[m_Columns.m_col_name]       = "Billy Bob";
    row[m_Columns.m_col_number]     = 10;
    row[m_Columns.m_col_percentage] = 15;

    row                             = *(m_refTreeModel->append());
    row[m_Columns.m_col_id]         = 2;
    row[m_Columns.m_col_name]       = "Joey Jojo";
    row[m_Columns.m_col_number]     = 20;
    row[m_Columns.m_col_percentage] = 40;

    row                             = *(m_refTreeModel->append());
    row[m_Columns.m_col_id]         = 3;
    row[m_Columns.m_col_name]       = "Rob McRoberts";
    row[m_Columns.m_col_number]     = 30;
    row[m_Columns.m_col_percentage] = 70;

    // Add the TreeView's view columns:
    // This number will be shown with the default numeric formatting.
    m_TreeView.append_column("Title", m_Columns.m_col_id);
    m_TreeView.append_column("Album", m_Columns.m_col_name);

    m_TreeView.append_column_numeric("Artist", m_Columns.m_col_number, "%010d" /* 10 digits, using leading zeroes. */);

    // Display a progress bar instead of a decimal number:
    auto cell       = Gtk::make_managed<Gtk::CellRendererProgress>();
    int  cols_count = m_TreeView.append_column("Duration", *cell);
    auto pColumn    = m_TreeView.get_column(cols_count - 1);
    if (pColumn)
    {
        pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
    }

    // Make all the columns reorderable:
    // This is not necessary, but it's nice to show the feature.
    // You can use TreeView::set_column_drag_function() to more
    // finely control column drag and drop.
    for (guint i = 0; i < 2; i++)
    {
        auto column = m_TreeView.get_column(i);
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