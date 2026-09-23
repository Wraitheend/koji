// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <gtkmm.h>
#include "components/player.h"

class Window : public Gtk::Window
{
  public:
    Window();
    virtual ~Window();

  protected:
    // Main
    Gtk::Notebook tabbar_notebook;

    Player player;

  private:
    bool onWindowKeyPressed(guint keyval, guint keycode, Gdk::ModifierType state);
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

    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(sigc::mem_fun(*this, &Window::onWindowKeyPressed), false);
    add_controller(controller);
}

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Minus) && player_context.volume - 5 >= 0)
//         updateVolume(player_context, -5);

//     if (ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Equal) && player_context.volume + 5 <= 100)
//         updateVolume(player_context, 5);

bool Window::onWindowKeyPressed(guint keyval, guint, Gdk::ModifierType state)
{
    if (keyval == GDK_KEY_Escape) // - `Esc`: Quits the program
    {
        close();
        return true;
    }
    else if (keyval == GDK_KEY_s) // - `S`: Toggle shuffle
    {
        player.toggleShuffle();
        return true;
    }
    else if (keyval == GDK_KEY_r) // - `R`: Toggle repeat mode
    {
        player.toggleRepeat();
        return true;
    }
    else if (keyval == GDK_KEY_x) // - `X`: Stop music
    {
        player.stopPlayback();
        return true;
    }
    else if (keyval == GDK_KEY_space) // - `Space Bar`: Toggle pause
    {
        player.togglePause();
        return true;
    }
    else if (keyval == GDK_KEY_equal && player.volume + 5 <= 100) // - `+`: Increase volume by 5%
    {
        player.volume += 5;
        player.updateVolume();
        return true;
    }
    else if (keyval == GDK_KEY_minus && player.volume - 5 >= 0) // - `-`: Decrease volume by 5%
    {
        player.volume -= 5;
        player.updateVolume();
        return true;
    }
    else if (keyval == GDK_KEY_Tab) // - `Tab`: Cycle tabs
    {
        const int current_page = tabbar_notebook.get_current_page();
        const int pages        = tabbar_notebook.get_n_pages();

        if (current_page + 1 >= pages)
            tabbar_notebook.set_current_page(0);
        else
            tabbar_notebook.set_current_page(current_page + 1);

        return true;
    }

    return false;
}

Window::~Window() {}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("cc.silverfiles.koji");

    // Shows the window and returns when it is closed.
    return app->make_window_and_run<Window>(argc, argv);
}