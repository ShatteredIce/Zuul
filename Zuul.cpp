//C++ Project 6 - Nathan Purwosumarto - 12/7/2016
//Zuul - A simple rpg with basic commands

#include <iostream>
#include <vector>
#include "Room.h"

using namespace std;

//Item variables
struct Item {
  char name[81];
  char desc[81];
  char tag[81];
  Room* currentRoom;
  int damage;
  int defense;
};

//Enemy variables
struct Hostile {
  bool isAlive;
  Room* currentRoom;
  int hp;
  int priority;
};

//Player variables
struct Player {
  int hp;
  Room* currentRoom;
  char weapon[81];
  Hostile* closestEnemy;
};

void addItem(vector<Item>*, char*, char*, Room*, int, int);
void addRoom(vector<Room*>*, int, char*);
Hostile* getClosestEnemy(Room* myRoom, Hostile* droid1, Hostile* droid2, Hostile* droid3, Hostile* droid4);
void trimWhitespace(char* text);

int main()
{

  //Setup variables
  int numHostiles = 4;
  bool running = true;
  char input[81];
  char quit[5];
  strcpy(quit, "quit");
  // char yes[4];
  // strcpy(yes, "yes");
  // char no[3];
  // strcpy(no, "no");

  //Item vector
  vector<Item> allItems;
  vector<Item>* allItemsPointer = & allItems;

  //Room vector
  vector<Room*> rooms;

  //Create the rooms
  Room* inventory = new Room(0, "inventory");
  Room* test = new Room(1, "random description.");
  Room* hangar1 = new Room(1, "You are to the left of the hangar entrance.");
  Room* hangar2 = new Room(2, "You are at the hangar entrance.");
  Room* hangar3 = new Room(3, "You are to the right of the hangar entrance.");
  Room* hangar4 = new Room(4, "You are in the storage room of the left loading bay.");
  Room* hangar5 = new Room(5, "You are on the lower wing of the left loading bay.");
  Room* hangar6 = new Room(6, "You are on the lower side of the hangar, near the left loading bay.");
  Room* hangar7 = new Room(7, "You are on the lower left side of the hangar.");
  Room* hangar8 = new Room(8, "You are on the lower side of the hangar.");
  Room* hangar9 = new Room(9, "You are on the lower right side of the hangar.");
  Room* hangar10 = new Room(10, "You are on the lower side of the hangar, near the right loading bay.");
  Room* hangar11 = new Room(11, "You are on the lower wing of the right loading bay.");
  Room* hangar12 = new Room(12, "You are in the storage room of the right loading bay.");
  Room* hangar13 = new Room(13, "You are on the landing pad of the left loading bay. \n Your light interceptor is atop the landing pad.");
  Room* hangar14 = new Room(14, "You are on the far left side of the hangar.");
  Room* hangar15 = new Room(15, "You are on the left side of the hangar.");
  Room* hangar16 = new Room(16, "You are in the center of the hangar. \n A holographic map of the solar system is displayed here.");
  Room* hangar17 = new Room(17, "You are on the right side of the hangar.");
  Room* hangar18 = new Room(18, "You are on the far right side of the hangar.");
  Room* hangar19 = new Room(19, "You are on the landing pad of the right loading bay. \n A droid assault ship is atop the landing pad.");
  Room* hangar20 = new Room(20, "You are in the control tower of the left loading bay.");
  Room* hangar21 = new Room(21, "You are on the upper wing of the left loading bay.");
  Room* hangar22 = new Room(22, "You are on the upper side of the hangar, near the left loading bay.");
  Room* hangar23 = new Room(23, "You are on the upper left side of the hangar. There are a few sorch marks on the wall.");
  Room* hangar24 = new Room(24, "You are at the front of the hangar. \n A large glass window overlooks the view into space.");
  Room* hangar25 = new Room(25, "You are on the upper right side of the hangar. There is a table and a few chairs.");
  Room* hangar26 = new Room(26, "You are on the upper side of the hangar, near the right loading bay.");
  Room* hangar27 = new Room(27, "You are on the upper wing of the right loading bay.");
  Room* hangar28 = new Room(28, "You are in the control tower of the right loading bay.");
  Room* ship = new Room(29, "You are in your light interceptor");
  
  //Add rooms to vector
  rooms.push_back(inventory);
  rooms.push_back(test);
  rooms.push_back(hangar1);
  rooms.push_back(hangar2);
  rooms.push_back(hangar3);
  rooms.push_back(hangar4);
  rooms.push_back(hangar5);
  rooms.push_back(hangar6);
  rooms.push_back(hangar7);
  rooms.push_back(hangar8);
  rooms.push_back(hangar9);
  rooms.push_back(hangar10);
  rooms.push_back(hangar11);
  rooms.push_back(hangar12);
  rooms.push_back(hangar13);
  rooms.push_back(hangar14);
  rooms.push_back(hangar15);
  rooms.push_back(hangar16);
  rooms.push_back(hangar17);
  rooms.push_back(hangar18);
  rooms.push_back(hangar19);
  rooms.push_back(hangar20);
  rooms.push_back(hangar21);
  rooms.push_back(hangar22);
  rooms.push_back(hangar23);
  rooms.push_back(hangar24);
  rooms.push_back(hangar25);
  rooms.push_back(hangar26);
  rooms.push_back(hangar27);
  rooms.push_back(hangar28);
  rooms.push_back(ship);

  // addItem(allItemsPointer, "test item", "desc", "my tag", test, 8, 6);
  //addItem(allItemsPointer, "itens", "desc2", "fri", test, 0, -1);

  //Create the enemies
  Hostile droid1;
  Hostile* droidPointer1 = & droid1;
  droid1.isAlive = true;
  droid1.currentRoom = hangar16;
  droid1.hp = 10;

  Hostile droid2;
  Hostile* droidPointer2 = & droid2;
  droid2.isAlive = true;
  droid2.currentRoom = hangar10;
  droid2.hp = 10;

  Hostile droid3;
  Hostile* droidPointer3 = & droid3;
  droid3.isAlive = true;
  droid3.currentRoom = hangar18;
  droid3.hp = 10;

  Hostile droid4;
  Hostile* droidPointer4 = & droid4;
  droid4.isAlive = true;
  droid4.currentRoom = hangar27;
  droid4.hp = 10;

  //Create the player
  Player player;
  player.hp = 20;
  player.currentRoom = hangar2;
  player.closestEnemy = getClosestEnemy(player.currentRoom, droidPointer1, droidPointer2, droidPointer3, droidPointer4);

  cout << "Current Room Id: " << player.currentRoom->getId() << " Closest Enemy Room Id: " << player.closestEnemy->currentRoom->getId() << endl;
  
  /*for(int a = 0; a < allItems.size(); a++){
    cout << allItems[a].name << " " << allItems[a].tag << " " << (allItems[a].currentRoom)->getId() << " " << allItems[a].defense << endl;
  }

  for(int a = 0; a < rooms.size(); a++){
    cout << rooms[a]->getId() << " " << rooms[a]->getDesc() << endl;
    }*/

  //get user input while game is running
  while(running){
    fill(input, input + 81, ' ');
    cout << "Enter action: ";
    cin.getline(input, 81);
    trimWhitespace(input);
    //if input = quit, prompt user if they want to exit the game
    if(strcmp(input, quit) == 0){
      fill(input, input + 81, ' ');
      cout << "Are you sure you want to quit? (y/n): ";
      cin.getline(input, 81);
      trimWhitespace(input);
      if(strcmp(input, "yes") == 0 || strcmp(input, "y") == 0){
	running = false;
	cout << "Program terminated." << endl;
      }
    }
  }
  
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

Hostile* getClosestEnemy(Room* myRoom, Hostile* droid1, Hostile* droid2, Hostile* droid3, Hostile* droid4){
  if(myRoom->getId() == 11 || myRoom->getId() == 12 || myRoom->getId() == 10){
    if(droid2->isAlive){
      return droid2;
    }
    else if(droid3->isAlive){
      return droid3;
    }
    else if(droid4->isAlive){
      return droid4;
    }
    else if(droid1->isAlive){
      return droid1;
    }
  }
  else if(myRoom->getId() == 26 || myRoom->getId() == 28 || myRoom->getId() == 27){
    if(droid4->isAlive){
      return droid4;
    }
    else if(droid3->isAlive){
      return droid3;
    }
    else if(droid2->isAlive){
      return droid2;
    }
    else if(droid1->isAlive){
      return droid1;
    }
  }
  else if(myRoom->getId() == 19 || myRoom->getId() == 18){
    if(droid3->isAlive){
      return droid3;
    }
    else if(droid2->isAlive){
      return droid2;
    }
    else if(droid4->isAlive){
      return droid4;
    }
    else if(droid1->isAlive){
      return droid1;
    }
  }
  else if(myRoom->getId() == 13 || myRoom->getId() == 14 || myRoom->getId() == 15 || myRoom->getId() == 16 || myRoom->getId() == 17 || \
	  myRoom->getId() == 29){
    if(droid1->isAlive){
      return droid1;
    }
    else if(droid3->isAlive){
      return droid3;
    }
    else if(droid2->isAlive){
      return droid2;
    }
    else if(droid4->isAlive){
      return droid4;
    }
  }
  else if(myRoom->getId() == 20 || myRoom->getId() == 21 || myRoom->getId() == 22 || myRoom->getId() == 23 || myRoom->getId() == 24 || \
	  myRoom->getId() == 25){
    if(droid1->isAlive){
      return droid1;
    }
    else if(droid3->isAlive){
      return droid3;
    }
    else if(droid4->isAlive){
      return droid4;
    }
    else if(droid2->isAlive){
      return droid2;
    }
  }
  else{
    if(droid1->isAlive){
      return droid1;
    }
    else if(droid2->isAlive){
      return droid2;
    }
    else if(droid3->isAlive){
      return droid3;
    }
    else if(droid4->isAlive){
      return droid4;
    }
  }
}

//remove extra whitespaces to make sure string compares function as intended
void trimWhitespace(char* text){
  char* newText = text;
  char lastChar = ' ';
  while(*text != '\0'){
    if(!(*text == ' ' && lastChar == ' ')){
      *newText = *text;
      lastChar = *text;
      newText++;
    }
    text++;
  }
  if(*(newText-1) != ' '){
    *newText = '\0';
  }
  else{
    *(newText-1) = '\0';
  }
}
