#include "mbox.h"

#include <iostream>
#include <sstream>

void read_box(const char* box, deque<message> &boxen){
  // "/home/dan/.getmail/gmail-backup.mbox"
  ifstream i(box);
  message m;
  ostringstream line;
  while(i){
    // Read Header
    while(i){
      string temp = "";
      getline(i,temp);
      if(temp == "")
        break;
      else if(temp.substr(0,5) == "From:"){
        m.from = temp.substr(6);
      }
      else if(temp.substr(0,9) == "Reply-to:"){
        m.replyto = temp.substr(10);
      }
      else if(temp.substr(0,3) == "To:"){
        m.to = temp.substr(4);
      }
      else if(temp.substr(0,8) == "Subject:"){
        m.subject = temp.substr(9);
      }
      else if(temp.substr(0,5) == "Date:"){
        m.date = temp.substr(6);
      }
      else{
        m.other = m.other + temp + '\n';
      }
    }
    // Read body
    while(i){
      string temp="";
      getline(i, temp);
      // New mail section
      if(temp.find("From")==0){
        string output = line.str();
        if(output.size()>2 && output.substr(output.size()-2)=="\n\n"){
          m.body = output;
          line.str(temp + '\n');
          break;
        }
      }
      else if(!i){
        m.body = line.str() + temp;
        break;
      }
      line << temp << '\n';
      temp = "";
    }
    boxen.push_front(m);
    m.clear();
  }
}

