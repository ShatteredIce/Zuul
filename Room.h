#include <iostream>
#include <string.h>
#include <map>

using namespace std;

//Header file for Room.cpp
//Stores values: id (int), description (char*), and exits (map)

class Room {
 public:
  Room(int, char*);
  int getId();
  char* getDesc();
  void setExit(int direction, Room* exit);
  Room* getExit(int exit);
 protected:
  int id;
  char* desc;
  map<int, Room*> movementMap;
};
