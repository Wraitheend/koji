// SPDX-License-Identifier: GPL-3.0
// SPDX-FileCopyrightText: 2026 silver_gray
#pragma once

#include <gtkmm.h>
#include "../player/player.h"

class Footer : public Gtk::Box
{
public:
    Footer();

    void update(const Player &player);

private:
    Gtk::Box       status_row{Gtk::Orientation::HORIZONTAL, 8};
    Gtk::Separator divider;

    Gtk::Label status_label;
    Gtk::Label time_label;
    Gtk::Label volume_label;
    Gtk::Label shuffle_label;
    Gtk::Label repeat_label;
    Gtk::Label hint_label;
};