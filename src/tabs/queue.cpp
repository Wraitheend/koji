#include <iostream>
#include <string>
#include <gtkmm.h>

class QueueColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    QueueColumns()
    {
        add(column_title);
        add(column_album);
        add(column_artist);
        add(column_duration);
        add(column_queue_index);
    }

    Gtk::TreeModelColumn<Glib::ustring> column_title;
    Gtk::TreeModelColumn<Glib::ustring> column_album;
    Gtk::TreeModelColumn<Glib::ustring> column_artist;
    Gtk::TreeModelColumn<Glib::ustring> column_duration;
    Gtk::TreeModelColumn<int>           column_queue_index;
};