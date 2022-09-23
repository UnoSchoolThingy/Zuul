#include "Item.h"

Item::Item(const char* name) {
  strcpy(this->name, name);
}

char* Item::getName() {
  return name;
}
