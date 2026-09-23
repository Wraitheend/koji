// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <iostream>
#include <gtkmm.h>

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Signal handlers:
    void onNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    // Child widgets:
    Gtk::Notebook tabbar_notebook;
    Gtk::Label    queue_label, album_label, playlist_label;
};

Window::Window() : queue_label("Contents of queue tab"), album_label("Contents of album tab"), playlist_label("Contents of playlist tab")
{
    set_title("Koji");
    set_default_size(400, 200);
    set_child(tabbar_notebook);

    // Add the Notebook pages:
    tabbar_notebook.append_page(queue_label, "Queue");
    tabbar_notebook.append_page(album_label, "Albums");
    tabbar_notebook.append_page(playlist_label, "Playlists");

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