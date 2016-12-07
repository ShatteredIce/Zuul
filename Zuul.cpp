//C++ Project 6 - Nathan Purwosumarto - 12/7/2016
//Zuul - A simple rpg with basic commands

#include <iostream>
#include <vector>
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
  char desc[81];
  char tag[81];
  Room* currentRoom;
  int damage;
  int defense;
};

void addItem(vector<Item>*, char*, char*, Room*, int, int);
void addRoom(vector<Room*>*, int, char*);

int main()
{

  //Item vector
  vector<Item> allItems;
  vector<Item>* allItemsPointer = & allItems;


  //Room vector
  vector<Room*> rooms;

  //Create the rooms
  Room* inventory = new Room(0, "inventory");
  Room* test = new Room(1, "random description");
  Room* hangar1 = new Room(1, "You are to the left of the hangar entrance");
  Room* hangar2 = new Room(2, "You are at the hangar entrance");
  Room* hangar3 = new Room(3, "You are to the right of the hangar entrance");
  Room* hangar4 = new Room(4, "You are on the far left wing of the left loading bay"); 
  
  //Add rooms to vector
  rooms.push_back(inventory);
  rooms.push_back(test);

  addItem(allItemsPointer, "test item", "desc", "my tag", test, 8, 6);
  addItem(allItemsPointer, "itens", "desc2", "fri", test, 0, -1);

  //Create the player
  Player player;
  player.hp = 20;
  player.currentRoom = test;
  
  
  /*for(int a = 0; a < allItems.size(); a++){
    cout << allItems[a].name << " " << allItems[a].tag << " " << (allItems[a].currentRoom)->getId() << " " << allItems[a].defense << endl;
  }

  for(int a = 0; a < rooms.size(); a++){
    cout << rooms[a]->getId() << " " << rooms[a]->getDesc() << endl;
    }*/
  
  return 0;
}

void addItem(vector<Item>* allItems, char* newName, char* newDesc, char* newTag, Room* startingRoom, int newDamage, int newDefense){
  Item item;
  strcpy(item.name, newName);
  strcpy(item.desc, newDesc);
  strcpy(item.tag, newTag);
  item.currentRoom = startingRoom;
  item.damage = newDamage;
  item.defense = newDefense;
  allItems->push_back(item);
}
