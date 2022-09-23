#pragma once

#include <iostream>
#include <cstring>

class Item {
 private:
  char name[50];
 public:
  Item(const char* name);
  char* getName();
};
