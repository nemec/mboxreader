#ifndef GTKMM_WINDOW_H
#define GTKMM_WINDOW_H


#include <gtkmm.h>
#include "mbox.h"


class Window : public Gtk::Window{

private:
  static const char* DEFAULT_MBOX_FILE;

  void initialize(const char* mboxpath);

public:
  Window();
  Window(const char* mboxpath);
  virtual ~Window();

protected:
  //Signal handlers:
  void on_button_quit();

  void build_tree_model(const char* mboxpath);
  
  void on_row_activated(const Gtk::TreeModel::Path& rowPath, Gtk::TreeViewColumn* column);

  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord{
  public:

    ModelColumns()
    { add(m_col_from); add(m_col_subject); add(m_col_date);}

    Gtk::TreeModelColumn<Glib::ustring> m_col_from;
    Gtk::TreeModelColumn<Glib::ustring> m_col_subject;
    Gtk::TreeModelColumn<Glib::ustring> m_col_date;
  };

  ModelColumns m_Columns;
  deque<message> box;
  //Child widgets:
  Gtk::VBox m_VBox;

  Gtk::ScrolledWindow m_ListScrolledWindow;
  Gtk::ScrolledWindow msg_ListScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Gtk::TextView m_TextView;
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  Gtk::HButtonBox m_ButtonBox;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_WINDOW_H

