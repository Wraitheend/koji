// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <iostream>
#include <gtkmm.h>
#include <string>

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

    Gtk::ListBox queue_box;
    Gtk::Box     queue_container;
    Gtk::Label    queue_label;
    
    Gtk::Label album_label, playlist_label;
};

Window::Window() : queue_label("Contents of queue tab"), album_label("Contents of album tab"), playlist_label("Contents of playlist tab")
{
    set_title("Koji");
    set_default_size(1920, 1080);
    set_child(tabbar_notebook);

    queue_label.set_valign(Gtk::Align::START);
    album_label.set_valign(Gtk::Align::START);
    playlist_label.set_valign(Gtk::Align::START);

    queue_label.set_halign(Gtk::Align::START);
    album_label.set_halign(Gtk::Align::START);
    playlist_label.set_halign(Gtk::Align::START);

    // queue_box.set_margin_top();
    
    queue_container.append(queue_label);
    queue_container.append(queue_box);
    

    // Add the Notebook pages:
    tabbar_notebook.append_page(queue_container, "Queue");
    tabbar_notebook.append_page(album_label, "Albums");
    tabbar_notebook.append_page(playlist_label, "Playlists");


    for (int i = 0; i < 5; ++i) {
        auto button = Gtk::Button(Glib::ustring("Queue Item " + std::to_string(i)));
        
        // Optional: Connect signal
        // button.signal_clicked().connect(sigc::mem_fun(*this, &Window::onButtonClick));

        button.set_valign(Gtk::Align::START);
        button.set_halign(Gtk::Align::START);

        queue_box.append(button);
    }

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