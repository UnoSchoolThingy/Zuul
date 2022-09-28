#include "Room.h"

Room::Room(const char* name, const char* desc) {
  strcpy(this->name, name);
  strcpy(this->desc, desc);
}

void Room::addExit(int position, Room* exit) {
  exits[position] = exit;
}

void Room::addItem(Item* item) {
  items.push_back(item);
}

void Room::removeItem(Item* item) {
  for (int i = 0; i < items.size(); i++) {
    if (items[i] == item) {
      items.erase(items.begin() + i);
      return;
    }
  }
}

vector<Item*> Room::getItems() {
  return items;
}

char* Room::getName() {
  return name;
}

char* Room::getDescription() {
  return desc;
}

Room* Room::getRoomAtExit(int exit) {
  return exits[exit];
}

Room* Room::getRoomFromExitChar(char c) {
  static map<char, int> m = {
     { 'n', POS_NORTH },
     { 's', POS_SOUTH },
     { 'e', POS_EAST },
     { 'w', POS_WEST },
  };
  if (m.count(c) < 1) return nullptr;
  return exits[m[c]];
}

vector<pair<int, Room*>> Room::getExits() {
  return vector<pair<int, Room*>>(exits.begin(), exits.end());
}

const char* Room::getExitName(int pos) {
   static map<int, const char*> exitNames = {
    { 0, "North" },
    { 1, "South" },
    { 2, "East" },
    { 3, "West" }
  };
  return exitNames[pos];
}
