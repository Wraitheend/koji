// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <gtkmm.h>
#include "components/components.h"

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

    Player player;
};

Window::Window()
{
    set_title("Koji");
    set_default_size(1920, 1080);
    set_child(tabbar_notebook);

    // Add the TreeView, inside a ScrolledWindow, with the button underneath:

    // Add the Notebook pages:
    if (!player.init())
        return;
    
    tabbar_notebook.append_page(player.queue.box, "Queue");
    tabbar_notebook.append_page(player.albums.box, "Albums");
    tabbar_notebook.append_page(player.playlists.box, "Playlists");

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