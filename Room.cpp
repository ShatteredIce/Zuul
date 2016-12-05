#include <iostream>
#include <string.h>
#include "Room.h"

using namespace std;

//Room class for Zuul.cpp

Room::Room(int newId, char* newDesc){
  id = newId;
  desc = newDesc;
}


int Room::getId() {
  return id;
}


char* Room::getDesc(){
  return desc;
}
