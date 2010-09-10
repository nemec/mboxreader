#include <gtkmm/main.h>
#include "window.h"

int main (int argc, char *argv[]){
  Gtk::Main kit(argc, argv);

  if(argc == 2){
    Window window(argv[1]);

    //Shows the window and returns when it is closed.
    Gtk::Main::run(window);
  }
  else{
    Window window;

    Gtk::Main::run(window);
  }

  return 0;
}

