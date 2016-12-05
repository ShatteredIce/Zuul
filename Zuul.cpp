//C++ Project 6 - Nathan Purwosumarto - 12/7/2016
//Zuul - A simple rpg with basic commands

#include <iostream>
#include "Room.h"

using namespace std;

//Player variables
struct Player {
  int hp;
  Room* currentRoom;
  char weapon[81];
};

//Item variables
struct Item {
  char name[81];
  char tag[81];
  Room* currentRoom;
  int damage;
  int defense;
};
  

int main()
{

  Room* test = new Room(1, "random description");
  cout << "My test room Id: " << test->getId() << "\nMy test room description: " << test->getDesc() << endl;

  
  
  return 0;
}
