#include <iostream>
#include <string.h>

using namespace std;

//Header file for Room.cpp

class Room {
 public:
  Room(int, char*);
  int getId();
  char* getDesc();
 protected:
  int id;
  char* desc;
};
