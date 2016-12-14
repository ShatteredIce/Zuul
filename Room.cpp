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

void Room::setExit(int direction, Room* newExit){
  movementMap[direction] = newExit;
}

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
