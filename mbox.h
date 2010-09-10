#ifndef MBOXREADER_H
#define MBOXREADER_H

#include <string>
#include <fstream>
#include <deque>

using namespace std;

struct message{
  string other;
  string from;
  string replyto;
  string to;
  string subject;
  string date;
  string body;
 
  message(){ clear(); }

  void clear(){
    other = from = replyto = to = subject = date = body = "";
  }
};

void read_box(const char* box, deque<message> &boxen);

#endif // MBOXREADER_H

