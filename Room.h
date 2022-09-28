#pragma once

#include "Item.h"
#include <vector>
#include <map>
#include <memory>
#include <set>

using std::map; using std::vector; using std::pair;

class Room {
 private:
  char name[50];
  char desc[100];
  map<int, Room*> exits;
  vector<Item*> items;
 public:
  static const int POS_NORTH = 0;
  static const int POS_SOUTH = 1;
  static const int POS_EAST = 2;
  static const int POS_WEST = 3;
  Room(const char* name, const char* desc);
  void addExit(int position, Room* exit);
  void addItem(Item* item);
  void removeItem(Item* item);
  vector<Item*> getItems(); 
  char* getName();
  char* getDescription();
  Room* getRoomAtExit(int exit);
  Room* getRoomFromExitChar(char c);
  vector<pair<int, Room*>> getExits();
  static const char* getExitName(int pos);
};
