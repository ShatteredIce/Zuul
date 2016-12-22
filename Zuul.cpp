//C++ Project 6 - Nathan Purwosumarto - 12/7/2016
//Zuul - A simple rpg with basic commands

#include <iostream>
#include <vector>
#include "Room.h"
#include <map>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

using namespace std;

//Item variables
struct Item {
  char name[81];
  char desc[181];
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

//Function prototypes
void addItem(vector<Item>*, char*, char*, char*, Room*, int, int);
void addRoom(vector<Room*>*, int, char*);
Hostile* getClosestEnemy(Room* myRoom, Hostile* droid1, Hostile* droid2, Hostile* droid3, Hostile* droid4);
void getInput(char* text);
void parseInput(char* text, char* command, char* object);
void trimWhitespace(char* text);
void displayRoom(Player* player, vector<Item>* allItems, Hostile* droid1, Hostile* droid2, Hostile* droid3, Hostile* droid4);
void hostileActions(Player* player, int numHostiles);

int main()
{
  srand(time(NULL));

  //Setup variables
  int numHostiles = 4;
  bool running = true;
  bool foundItem = false;
  int hit = 0;
  int gunHeat = 0;
  int movementDirection = 0;
  //Input variables
  char input[81];
  char command[81];
  char object[81];
  char quit[5];
  //General commands
  strcpy(quit, "quit");
  char move[5];
  strcpy(move, "move");
  char north[6];
  strcpy(north, "north");
  char east[5];
  strcpy(east, "east");
  char south[6];
  strcpy(south, "south");
  char west[5];
  strcpy(west, "west");
  char take[5];
  strcpy(take, "take");
  char drop[5];
  strcpy(drop, "drop");
  char examine[8];
  strcpy(examine, "examine");
  char use[4];
  strcpy(use, "use");
  char enter[6];
  strcpy(enter, "enter");
  char exit[5];
  strcpy(exit, "exit");
  char help[5];
  strcpy(help, "help");

  //Create the map linking room exits
  map <int, Room*> movementMap;

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
  Room* hangar13 = new Room(13, "You are on the landing pad of the left loading bay. \nYour light interceptor is atop the landing pad.");
  Room* hangar14 = new Room(14, "You are on the far left side of the hangar.");
  Room* hangar15 = new Room(15, "You are on the left side of the hangar.");
  Room* hangar16 = new Room(16, "You are in the center of the hangar. \nA holographic map of the solar system is displayed here.");
  Room* hangar17 = new Room(17, "You are on the right side of the hangar.");
  Room* hangar18 = new Room(18, "You are on the far right side of the hangar.");
  Room* hangar19 = new Room(19, "You are on the landing pad of the right loading bay. \nA droid assault ship is atop the landing pad.");
  Room* hangar20 = new Room(20, "You are in the control tower of the left loading bay.");
  Room* hangar21 = new Room(21, "You are on the upper wing of the left loading bay.");
  Room* hangar22 = new Room(22, "You are on the upper side of the hangar, near the left loading bay.");
  Room* hangar23 = new Room(23, "You are on the upper left side of the hangar. \nThere are a few sorch marks on the wall.");
  Room* hangar24 = new Room(24, "You are at the front of the hangar. \nA large glass window overlooks the view into space.");
  Room* hangar25 = new Room(25, "You are on the upper right side of the hangar. There is a table and a few chairs.");
  Room* hangar26 = new Room(26, "You are on the upper side of the hangar, near the right loading bay.");
  Room* hangar27 = new Room(27, "You are on the upper wing of the right loading bay.");
  Room* hangar28 = new Room(28, "You are in the control tower of the right loading bay.");
  Room* ship = new Room(29, "");
  Room* usedItems = new Room(30, "dummy room for used up items");

  //Assign exits to rooms
  hangar1->setExit(1, hangar7);
  hangar1->setExit(2, hangar2);
  hangar2->setExit(1, hangar8);
  hangar2->setExit(2, hangar3);
  hangar2->setExit(4, hangar1);
  hangar3->setExit(1, hangar9);
  hangar3->setExit(4, hangar2);
  hangar4->setExit(2, hangar5);
  hangar5->setExit(1, hangar13);
  hangar5->setExit(2, hangar6);
  hangar5->setExit(4, hangar4);
  hangar6->setExit(1, hangar14);
  hangar6->setExit(2, hangar7);
  hangar6->setExit(4, hangar5);
  hangar7->setExit(1, hangar15);
  hangar7->setExit(2, hangar8);
  hangar7->setExit(3, hangar1);
  hangar7->setExit(4, hangar6);
  hangar8->setExit(1, hangar16);
  hangar8->setExit(2, hangar9);
  hangar8->setExit(3, hangar2);
  hangar8->setExit(4, hangar7);
  hangar9->setExit(1, hangar17);
  hangar9->setExit(2, hangar10);
  hangar9->setExit(3, hangar3);
  hangar9->setExit(4, hangar8);
  hangar10->setExit(1, hangar18);
  hangar10->setExit(2, hangar11);
  hangar10->setExit(4, hangar9);
  hangar11->setExit(1, hangar19);
  hangar11->setExit(2, hangar12);
  hangar11->setExit(4, hangar10);
  hangar12->setExit(4, hangar11);
  hangar13->setExit(1, hangar21);
  hangar13->setExit(2, hangar14);
  hangar13->setExit(3, hangar5);
  hangar14->setExit(1, hangar22);
  hangar14->setExit(2, hangar15);
  hangar14->setExit(3, hangar6);
  hangar14->setExit(4, hangar13);
  hangar15->setExit(1, hangar23);
  hangar15->setExit(2, hangar16);
  hangar15->setExit(3, hangar7);
  hangar15->setExit(4, hangar14);
  hangar16->setExit(1, hangar24);
  hangar16->setExit(2, hangar17);
  hangar16->setExit(3, hangar8);
  hangar16->setExit(4, hangar15);
  hangar17->setExit(1, hangar25);
  hangar17->setExit(2, hangar18);
  hangar17->setExit(3, hangar9);
  hangar17->setExit(4, hangar16);
  hangar18->setExit(1, hangar26);
  hangar18->setExit(2, hangar19);
  hangar18->setExit(3, hangar10);
  hangar18->setExit(4, hangar17);
  hangar19->setExit(1, hangar27);
  hangar19->setExit(3, hangar11);
  hangar19->setExit(4, hangar18);
  hangar20->setExit(2, hangar21);
  hangar21->setExit(2, hangar22);
  hangar21->setExit(3, hangar13);
  hangar21->setExit(4, hangar20);
  hangar22->setExit(2, hangar23);
  hangar22->setExit(3, hangar14);
  hangar22->setExit(4, hangar21);
  hangar23->setExit(2, hangar24);
  hangar23->setExit(3, hangar15);
  hangar23->setExit(4, hangar22);
  hangar24->setExit(2, hangar25);
  hangar24->setExit(3, hangar16);
  hangar24->setExit(4, hangar23);
  hangar25->setExit(2, hangar26);
  hangar25->setExit(3, hangar17);
  hangar25->setExit(4, hangar24);
  hangar26->setExit(2, hangar27);
  hangar26->setExit(3, hangar18);
  hangar26->setExit(4, hangar25);
  hangar27->setExit(2, hangar28);
  hangar27->setExit(3, hangar19);
  hangar27->setExit(4, hangar26);
  hangar28->setExit(4, hangar27);

  

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

  //Create the items
  addItem(allItemsPointer, "laser pistol", "You examine your laser pistol. It seems to be in working order.", "weapon", ship, 3, 0);
  addItem(allItemsPointer, "energy cell", "You examine the energy cell. It glows a faint blue.", " ", hangar1, 0, 0);
  addItem(allItemsPointer, "emp grenade", "You examine the EMP grenade. It is a round metal ball that is capable of shutting down electronics for a short time.", "useable", hangar25, 1, 0);
  addItem(allItemsPointer, "music box", "You examine the music box. It seems to be very old.", "useable", hangar20, 0 ,0);
  addItem(allItemsPointer, "mineral sample", "You examine the mineral sample. It is labeled CR-9782-045.", " ", hangar3, 0, 0);
  addItem(allItemsPointer, "broken mining drill", "You examine the broken mining drill. It doesn't seem to be repairable.", " ", hangar4, 0, 0);
  addItem(allItemsPointer, "metal plate", "You examine the metal plates. Nothing happens.", " ", hangar28, 0, 0);
  
  
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
  player.hp = 30;
  player.currentRoom = ship;
  player.closestEnemy = getClosestEnemy(player.currentRoom, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
  Player* playerPointer = & player;

  //Print the introduction to the game
  cout << "You are a pilot of the Lunar Federation.\n";
  cout << "You were assigned a mission to retrieve a mineral sample from an outpost of the planetoid X-120 in the Ymir system.\n";
  cout << "Upon entry into Ymir space, you were ambushed by a droid assault ship.\n";
  cout << "Despite taking heavy damage, you managed to land your interceptor in the left loading bay of the outpost.\n\n";
  cout << "Press enter to continue.\n";
  cin.ignore(81, '\n');
  cout << "-----Starship Navigation Computer-----\n\n";
  cout << "LOCATION: Planetoid X-120; Ymir System\n\n";
  cout << "-----STATUS:-----\n";
  cout << "-Shields offline. Hull and landing gear damaged.\n";
  cout << "-Sustainined critical damage to central energy cell. Weapon systems offline.\n";
  cout << "-Minor damage to right airfoil.\n\n";
  cout << "--------------------------------------\n";
  cout << "Press enter to continue.\n";
  cin.ignore(81, '\n');
  cout << "To complete the mission, retrieve the mineral sample and get it offworld.\n\n";
  cout << "General commands: MOVE, TAKE, DROP, INVENTORY, USE, EXAMINE, HELP, or QUIT\n";
  cout << "You are in your light interceptor.\n";
  cout << "Ship commands: TAKEOFF, SHOOT, LOG, or EXIT.";
  displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
  
  //get user input while game is running
  while(running){
    getInput(input);
    parseInput(input, command, object);
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
    //if input = help, print the command words
    else if(strcmp(input, "help") == 0){
      cout << "General commands: MOVE, TAKE, DROP, INVENTORY, USE, EXAMINE, HELP, or QUIT\n";
      cout << "You can ENTER or EXIT your light interceptor.";
      if(player.currentRoom->getId() != 29){
	cout << endl;
      }
      displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
    }
    //if input  = inventory, print the player's inventory
    else if(strcmp(input, "inventory") == 0){
      cout << "-----Your inventory-----\n";
      for(int i = 0; i < allItems.size(); i++){
	if(allItems[i].currentRoom->getId() == 0){
	  cout << " " << allItems[i].name << endl;
	}
      }
    }
    //if command = take, attempt to take the item the player specified
    else if(strcmp(command, take) == 0){
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	if(strcmp(object, allItems[i].name) == 0 && player.currentRoom->getId() == allItems[i].currentRoom->getId()){
	  cout << "You take the " << allItems[i].name << endl;
	  allItems[i].currentRoom = inventory;
	  foundItem = true;
	}
      }
      //if the specified item was not found
      if(foundItem == false){
	cout << "You cannot take that item.\n";
      }
    }
    //if command = drop, attempt to drop the item the player specified
    else if(strcmp(command, drop) == 0){
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	if(strcmp(object, allItems[i].name) == 0 && allItems[i].currentRoom->getId() == 0){
	  cout << "You drop the " << allItems[i].name << endl;
	  allItems[i].currentRoom = player.currentRoom;
	  foundItem = true;
	}
      }
      //if the specified item was not found
      if(foundItem == false){
	cout << "You cannot drop that item.";
      }
    }
    //if command = examine, attempt to examine the item the player specified
    else if(strcmp(command, examine) == 0){
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	if(strcmp(object, allItems[i].name) == 0 && (allItems[i].currentRoom->getId() == 0 || allItems[i].currentRoom->getId() == player.currentRoom->getId())){
	  cout << allItems[i].desc << endl;
	  foundItem = true;
	}
      }
      //if the specified item was not found
      if(foundItem == false){
	cout << "You cannot examine that item.";
      }
    }
    //if command = use, use item that the player specified
    else if(strcmp(command, use) == 0){
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	if(strcmp(object, allItems[i].name) == 0 && allItems[i].currentRoom->getId() == 0){
	  //use music box
	  if(strcmp(allItems[i].name, "music box") == 0){
	    cout << "You open up the ancient music box. It starts playing the soviet national anthem.\n";
	  }
	  //if player is in their ship, they cannot use the grenade or their laser pistol
	  else if(player.currentRoom->getId() == 29){
	    cout << "You cannot use that in here.\n";
	  }
	  //use the emp grenade
	  else if(strcmp(allItems[i].name, "emp grenade") == 0){
	    if(numHostiles > 0){
	      cout << "You throw the emp grenade at the nearest droid, causing it to short-circuit.\n";
	      player.closestEnemy->isAlive = false;
	      numHostiles--;
	      allItems[i].currentRoom = usedItems;
	      player.closestEnemy = getClosestEnemy(player.currentRoom, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	      cout << endl;
	      hostileActions(playerPointer, numHostiles);
	    }
	    //if all the droids are dead and the player attempts to use the emp grenade
	    else{
	      cout << "You have defeated all the droids in the hangar. You have no more use of this item.\n";
	    }
	  }
	  //use the laser pistol
	  else if(strcmp(object, "laser pistol") == 0){
	    if(gunHeat >= 5){
	      cout << "Your laser pistol is too hot to be used right now.\n";
	    }
	    else if(numHostiles > 0){
	      gunHeat++;
	      cout << "You take aim and fire at the nearest droid.\n";
	      hit = rand() % 3;
	      if(hit == 2){
		cout << "The laser bolt hits the droid, dealing moderate damage.\n";
		player.closestEnemy->hp -= 4;
	      }
	      else if(hit == 1){
		cout << "The laser bolt glances off the droid, dealing minor damage.\n";
		player.closestEnemy->hp -= 2;
	      }
	      else{
		cout << "The laser bolt misses the droid.\n";
	      }
	      //if the player manages to kill the droid with their shot
	      if(player.closestEnemy->hp <= 0){
		cout << "The droid explodes in a shower of sparks.\n";
		player.closestEnemy->isAlive = false;
		numHostiles--;
		player.closestEnemy = getClosestEnemy(player.currentRoom, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	      }
	      cout << endl;
	      hostileActions(playerPointer, numHostiles);
	    }
	    //if all the droids are dead and the player attempts to use the laser pistol
	    else{
	      cout << "You have defeated all the droids in the hangar. You fire at the wall, doing no damage.\n";
	    }
	  }
	  //if item does not have a use
	  else{
	    cout << "You cannot find a use for this item." << endl;
	  }
	  foundItem = true;
	}
      }
      //if specified item was not in their inventory
      if(foundItem == false){
	cout << "You do not have this item.\n";
      }
    }
    //enter the player's ship 
    else if(strcmp(command, enter) == 0){
      if(player.currentRoom->getId() == 13 && (strcmp(object, "ship") == 0 || strcmp(object, "light interceptor") == 0 || strcmp(object, "interceptor") == 0)){
	cout << "\nYou enter your light interceptor.\n";
	cout << "Ship commands: TAKEOFF, SHOOT, LOG, or EXIT.";
	player.currentRoom = ship;
	displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
      }
      else{
	cout << "Invalid command.\n";
      }
    }
    //exit the player's ship
    else if(strcmp(command, exit) == 0){
      if(player.currentRoom->getId() == 29 && (strcmp(object, "ship") == 0 || strcmp(object, "light interceptor") == 0 || strcmp(object, "interceptor") == 0)){
	cout << "\nYou exit your light interceptor.\n";
	player.currentRoom = hangar13;
	displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	player.closestEnemy = getClosestEnemy(player.currentRoom, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
      }
      else{
	cout << "Invalid command.\n";
      }
    }
    //end the game
    else if(strcmp(input, "takeoff") == 0 && player.currentRoom->getId() == 29){
      cout << "You fly off into space and leave the hangar behind.\n";
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	//if player has the mineral sample, say they won the game
	if(strcmp(allItems[i].name, "mineral sample") == 0 && (allItems[i].currentRoom->getId() == 0 || allItems[i].currentRoom->getId() == 29)){
	  cout << "\nYou have succesfully retrieved the mineral sample. Mission Complete!\n\n";
	  foundItem = true;
	}
      }
      //if player does not have the mineral sample, say they lost the game
      if(foundItem == false){
	cout << "\nThe mineral sample falls into enemy hands. Mission Failed.\n\n";
      }
      running = false;
    }
    //print out the ship's log
    else if(strcmp(input, "log") == 0 && player.currentRoom->getId() == 29){
      cout << "\n-----Starship Navigation Computer-----\n\n";
      cout << "LOCATION: Planetoid X-120; Ymir System\n\n";
      cout << "-----STATUS:-----\n";
      cout << "-Shields offline. Hull and landing gear damaged.\n";
      cout << "-Sustainined critical damage to central energy cell. Weapon systems offline.\n";
      cout << "-Minor damage to right airfoil.\n\n";
    }
    //attempt to shoot all the droids in the room 
    else if(strcmp(input, "shoot") == 0 && player.currentRoom->getId() == 29){
      foundItem = false;
      for(int i = 0; i < allItems.size(); i++){
	//if the player has the energy cell, kill off all the droids
	if(strcmp(allItems[i].name, "energy cell") == 0 && allItems[i].currentRoom->getId() == 0){
	  foundItem = true;
	  allItems[i].currentRoom = usedItems;
	  cout << "You use the energy cell to restore power to the weapon systems,\n";
	  if(numHostiles > 1){
	    cout << "then proceed to blast the remaining droids into oblivion.\n";
	    droid1.isAlive = false;
	    droid2.isAlive = false;
	    droid3.isAlive = false;
	    droid4.isAlive = false;
	    numHostiles = 0;
	  }
	  else if(numHostiles == 1){
	    cout << "then proceed to blast the single remaining droid into pieces.\n";
	    droid1.isAlive = false;
	    droid2.isAlive = false;
	    droid3.isAlive = false;
	    droid4.isAlive = false;
	    numHostiles = 0;
	  }
	  else{
	    cout << "All the droids have already been destroyed.\n";
	  }
	}	
      }
      //if the player does not have the energy cell
      if(foundItem == false){
	cout << "The weapon systems are down.\n";
      }
    }
    //move to an adjacent room
    else if(strcmp(command, move) == 0){
      movementDirection = 0;
      //move north
      if(strcmp(object, north) == 0 && player.currentRoom->getExit(1) != NULL){
	movementDirection = 1;
	player.currentRoom = player.currentRoom->getExit(1);
        displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	hostileActions(playerPointer, numHostiles);
	if(gunHeat != 0){
	  gunHeat--;
	}
      }
      //move east
      else if(strcmp(object, east) == 0 && player.currentRoom->getExit(2) != NULL){
	movementDirection = 2;
	player.currentRoom = player.currentRoom->getExit(2);
	displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	hostileActions(playerPointer, numHostiles);
	if(gunHeat != 0){
	  gunHeat--;
	}
      }
      //move south
      else if(strcmp(object, south) == 0 && player.currentRoom->getExit(3) != NULL){
	movementDirection = 3;
	player.currentRoom = player.currentRoom->getExit(3);
	displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
        hostileActions(playerPointer, numHostiles);
	if(gunHeat != 0){
	  gunHeat--;
	}
      }
      //move west
      else if(strcmp(object, west) == 0 && player.currentRoom->getExit(4) != NULL){
	movementDirection = 4;
	player.currentRoom = player.currentRoom->getExit(4);
	displayRoom(playerPointer, allItemsPointer, droidPointer1, droidPointer2, droidPointer3, droidPointer4);
	hostileActions(playerPointer, numHostiles);
	if(gunHeat != 0){
	  gunHeat--;
	}
      }
      else{
	cout << "You cannot move in that direction.\n";
      }
    }
    else{
      cout << "Invalid command.\n";
    }
    //if the player hp falls to 0
    if(player.hp <= 0){
      cout << "\nYou died!\n\n";
      running = false;
    }
  }
  
  return 0;
}

//gets the user input from the console
void getInput(char* text){
  fill(text, text + 81, ' ');
  cout << "------------------------";
  cout << "\nEnter action: ";
  cin.getline(text, 81);
  trimWhitespace(text);
  for(int i = 0; i < strlen(text); i++){
    text[i] = tolower(text[i]);
  }
}

//splits the input into a command word and an object
//command = the first word typed, object = everything else
void parseInput(char* text, char* command, char* object){
  while(*text != ' ' && *text != '\0'){
    *command = *text;
    command++;
    text++;
  }
  *command = '\0';
  if(*text == ' '){
    text++;
  }
  while(*text != '\0'){
    *object = *text;
    object++;
    text++;
  }
  *object = '\0';
}

//add an item to the game
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

//gets the closest enemy to the player
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

//displays the room
void displayRoom(Player* player, vector<Item>* allItems, Hostile* droid1, Hostile* droid2, Hostile* droid3, Hostile* droid4){
  cout << endl << player->currentRoom->getDesc() << endl;
  //prints room exits
  cout << "Movement directions:";
  if(player->currentRoom->getExit(1) != NULL){
    cout << " NORTH";
  }
  if(player->currentRoom->getExit(2) != NULL){
    cout << " EAST";
  }
  if(player->currentRoom->getExit(3) != NULL){
    cout << " SOUTH";
  }
  if(player->currentRoom->getExit(4) != NULL){
    cout << " WEST";
  }
  if(player->currentRoom->getId() == 29){
    cout << " EXIT";
  }
  //print items in the room
  cout << endl;
  for(int i = 0; i < allItems->size(); i++){
    if(player->currentRoom->getId() == allItems->at(i).currentRoom->getId()){
      cout << "A " << allItems->at(i).name << " is on the floor." << endl;
    }
  }
  cout << endl;
  //print messages for rooms with a battle droid or the landing pad
  if(player->currentRoom->getId() == 13){
    cout << "You may enter your light interceptor from here.\n\n"; 
  }
  if(player->currentRoom->getId() == 16 && droid1->isAlive == true){
    cout << "One of the battle droids is here.\n";
  }
  else if(player->currentRoom->getId() == 16){
    cout << "There are parts of a destroyed battle droid.\n";
  }
  else if(player->currentRoom->getId() == 10 && droid2->isAlive == true){
    cout << "One of the battle droids is here.\n";
  }
  else if(player->currentRoom->getId() == 10){
    cout << "There are parts of a destroyed battle droid.\n";
  }
  else if(player->currentRoom->getId() == 18 && droid3->isAlive == true){
    cout << "One of the battle droids is here.\n";
  }
  else if(player->currentRoom->getId() == 18){
    cout << "There are parts of a destroyed battle droid.\n";
  }
  else if(player->currentRoom->getId() ==  27 && droid4->isAlive == true){
    cout << "One of the battle droids is here.\n";
  }
  else if(player->currentRoom->getId() == 27){
    cout << "There are parts of a destroyed battle droid.\n";
  }
  player->closestEnemy = getClosestEnemy(player->currentRoom, droid1, droid2, droid3, droid4);
}

//remaining droids shoot the player after every move
void hostileActions(Player* player, int numHostiles){
  int move = 0;
  int hit = 0;
  //50% chance of moving, 33% chance of hitting the player
  for(int i = 0; i < numHostiles; i++){
    move = rand() % 2;
    hit = rand() % 3;
    if(move == 1 && hit == 2){
      cout << "A battle droid hits you with a laser bolt.\n";
      player->hp -= 2;
    }
    else if(move == 1){
      cout << "A laser bolt flies harmlessly past.\n";
    }
  }
}

