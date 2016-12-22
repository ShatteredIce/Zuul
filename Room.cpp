#include <iostream>
#include <string.h>
#include "Room.h"
#include <map>

using namespace std;

//Room class for Zuul.cpp

Room::Room(int newId, char* newDesc){
  id = newId;
  desc = newDesc;
}

//assigns an exit to the room
void Room::setExit(int direction, Room* newExit){
  movementMap[direction] = newExit;
}

//gets the exit, or returns null if there is no exit in that direction
//direction: north = 1, east = 2, south = 3, west = 4
Room* Room::getExit(int direction){
  map<int, Room*>::iterator iter;
  iter = movementMap.find(direction);
  if (iter != movementMap.end()){
    return movementMap.find(direction)->second;
  }
  else{
    return NULL;
  }
}

int Room::getId() {
  return id;
}


char* Room::getDesc(){
  return desc;
}
