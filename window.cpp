#include <iostream>
#include "window.h"

const char *Window::DEFAULT_MBOX_FILE = "/home/dan/.getmail/gmail-backup.mbox";

Window::Window() : m_Button_Quit("Quit"){
  initialize(DEFAULT_MBOX_FILE);
}

Window::Window(const char* mboxpath) : m_Button_Quit("Quit"){
  initialize(mboxpath);
}

void Window::initialize(const char* mboxpath){
  set_title("Mbox Reader");
  set_border_width(5);
  set_default_size(800, 600);

  add(m_VBox);

  //Add the TreeView, inside a ListScrolledWindow, with the button underneath:
  m_ListScrolledWindow.add(m_TreeView);
  // Add TextView to another scroll window
  msg_ListScrolledWindow.add(m_TextView);
  m_TextView.set_editable(false);
  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);
  msg_ListScrolledWindow.set_border_width(5);

  //Only show the scrollbars when they are necessary:
  m_ListScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  msg_ListScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ListScrolledWindow);
  m_VBox.pack_start(msg_ListScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &Window::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);
  m_TreeView.signal_row_activated().connect( sigc::mem_fun(*this,
              &Window::on_row_activated) );

  build_tree_model(mboxpath);

  show_all_children();
}

void Window::build_tree_model(const char* mboxpath){
  read_box(mboxpath, box);
  
  deque<message>::iterator i;
  for(i = box.begin(); i != box.end() ; i++){
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_from] = i->from;
    row[m_Columns.m_col_subject] = i->subject;
    row[m_Columns.m_col_date] = i->date;
  }

  //Add the TreeView's view columns:
  //This number will be shown with the default numeric formatting.
  m_TreeView.append_column("From", m_Columns.m_col_from);
  m_TreeView.append_column("Subject", m_Columns.m_col_subject);

  m_TreeView.append_column("Date", m_Columns.m_col_date);

  for(guint i = 0; i < 3; i++){
    Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
    //Make all the columns sortable
    pColumn->set_sort_column(i);
    pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
    switch(i){
      case 0: pColumn->set_fixed_width(200); break;
      case 1: pColumn->set_fixed_width(350); break;
      case 2: pColumn->set_fixed_width(50); break;
    }
    pColumn->set_resizable();
  }
}

Window::~Window(){
}

void Window::on_button_quit(){
  hide();
}

void Window::on_row_activated(const Gtk::TreeModel::Path& rowPath, Gtk::TreeViewColumn* column){
  istringstream i(rowPath.to_string());
  int ix;
  i >> ix;
  m_refTextBuffer->set_text(box[ix].body);
}

