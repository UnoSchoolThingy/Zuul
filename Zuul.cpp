/* Uno Pasadhika 
 * Zuul game - move around a school building 
 * 9/28/2022 
 */

#include "Room.h"

using namespace std;

inline vector<pair<int, int>> getAdj(int x, int y) {
  vector<pair<int, int>> res;
  if (y - 1 >= 0) res.push_back({x, y - 1}); // North
  else res.push_back({-1, -1});
  if (y + 1 < 5) res.push_back({x, y + 1}); // South
  else res.push_back({-1, -1});
  if (x + 1 < 6) res.push_back({x + 1, y}); // East
  else res.push_back({-1, -1});
  if (x - 1 >= 0) res.push_back({x - 1, y}); // West
  else res.push_back({-1, -1});
  return res;
}

int main() {
  vector<Room*> rooms = {
    new Room("1-20", "You are currently in the 1-20 lab at Sunset. All the cool people are hanging out here."), // 0
    new Room("CAD Room", "You care in the CAD room."), // 1 
    new Room("Outside", "You are outside. This area has four exits but no roof so it still counts as outside."), // 2
    new Room("Pub", "You are in the pub."), // 3
    new Room("Theatre", "You are in the theater. You almost get kicked out after screaming loudly to hear the echo."), // 4
    new Room("Computing Lab", "You are in the computing lab. As the name suggests, there are computers here."), // 5
    new Room("Computing Admin Office", "You are in the computing admin office."), // 6 
    new Room("Auditorium", "You are in the auditorium."), // 7
    new Room("Library", "You are in the library. You close the door too loud and the librarian yells at you to be quiet."), // 8
    new Room("Study Room", "You are in the study room. You notice that nobody is actually studying."), // 9
    new Room("Science Lab", "You are in the science lab."), // 10
    new Room("Medical Office", "You are in the medical office."), // 11 
    new Room("Gym", "You are at the gym."), // 12
    new Room("Store", "You are at the store."), // 13
    new Room("Math Classroom", "You are in the math classroom."), // 14
    new Room("Teacher's Lounge", "You are in the teacher's lounge.") // 15
  }; // Rooms vector (we only use the vector to connect the rooms) 
  vector<Item*> inv; // Player inventory
  // Add items to rooms
  rooms[0]->addItem(new Item("Robot")); // 1-20 
  rooms[3]->addItem(new Item("Pizza")); // Pub 
  rooms[8]->addItem(new Item("Horn")); // Library 
  rooms[12]->addItem(new Item("Basketball")); // Gym
  rooms[14]->addItem(new Item("Marker")); // Math Classroom
  // Visual map of the building (we could also just add things manually but this makes it easier to change the layout) 
  int building[5][6] = {
    { -1, -1, 15, 14, 13, -1 },
    { -1,  1, -1, -1, 12, -1 },
    { -1,  0, -1, -1, 11, -1 },
    {  3,  2,  4,  7,  8, 10 },
    { -1,  5,  6, -1,  9, -1 }
  };
  // Add connections
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 5; y++) {
      if (building[y][x] == -1) continue;
      auto pv = getAdj(x, y);
      for (int i = 0; i < 4; i++) {
	auto p = pv[i];
	if (p.first == -1 || building[p.second][p.first] == -1) continue;
	rooms[building[y][x]]->addExit(i, rooms[building[p.second][p.first]]);
      }
    }
  }
  // Setup done 
  cout << "Welcome to Zuul!\n";
  char in[100]; // String input 
  char inc; // Character input 
  int ini; // Integer input
  Room* r = rooms[0]; // Start at 1-20
  while (true) {
    // Lose case
    if (r == rooms[8]) { // If we are in the library
      for (Item* i : inv) {
	if (strcmp(i->getName(), "Horn") == 0) { // We picked up the horn last turn
	  cout << "The horn makes noise as you pick it up and you get kicked out. You lose.\n";
	  return 0;
	}
      }
    }
    // Win case
    if (r == rooms[3]) { // If we are in the pub 
      for (Item* i : inv) {
        if (strcmp(i->getName(), "Pizza") == 0) { // We picked up the pizza last turn 
          cout << "You have acquired a pizza. Pizza is good. You win.\n";
          return 0;
        }
      }
    }
    // Play the game 
    auto items = r->getItems();
    cout << "==============================\n";
    cout << r->getDescription() << "\n";
    cout << "Exits: \n";
    for (auto e : r->getExits()) {
      cout << Room::getExitName(e.first) << ": " << e.second->getName() << '\n';
    }
    cout << '\n';
    // Print room items 
    if (items.empty()) {
      cout << "There are no items in the room.\n";
    }
    else {
      cout << "Items in the room: \n";
      for (int i = 0; i < items.size(); i++) {
	cout << '[' << (i + 1) << "] " << items[i]->getName() << '\n';
      }
    }
    cout << endl; // New line and flush output stream
    // Print inventory items 
    if (inv.empty()) {
      cout << "There are no items in your inventory.\n";
    }
    else {
      cout << "Items in your inventory: \n";
      for (int i = 0; i < inv.size(); i++) {
        cout << '[' << (i + 1) << "] " << inv[i]->getName() << '\n';
      }
    }
    cout << endl; // New line and flush output stream 
    // Ask user for action (not making an actual system because I really don't want to open more emacs windows)
    while (true) {
      cout << "Pick up(p), drop(d), move(m), or quit(q): ";
      cin >> inc;
      cin.ignore();
      inc = tolower(inc);
      if (inc == 'q') {
	cout << "Thanks for playing!\n";
	return 0;
      }
      if (inc == 'p') {
      plab:
	if (items.empty()) {
	  cout << "There are no items in this room!\n";
	  continue;
	}
	cout << "Enter the room item number to pick up (listed above): ";
	cin >> inc; 
	if (!isdigit(inc)) {
	  cout << "Please enter a number!\n";
	  goto plab;
	}
	ini = inc - '0';
	cin.ignore(0);
	if (ini > items.size()) { // Make sure it's not out of range 
	  cout << "There's no item numbered " << ini << "!\n";
	  goto plab;
	}
	inv.push_back(items[--ini]);// Add item to inventory 
	r->removeItem(items[ini]); // Get rid of the item
	break;
      }
      if (inc == 'd') {
      dlab:
	if (inv.empty()) {
	  cout << "There are no items in your inventory!\n";
	  continue;
	}
        cout << "Enter the inventory item number to pick up (listed above): ";
        cin >> inc;
	if (!isdigit(inc)) {
          cout << "Please enter a number!\n";
          goto dlab;
        }
        ini = inc - '0';
        cin.ignore(0);
        if (ini > inv.size()) { // Make sure it's not out of range
          cout << "There's no item numbered " << ini << "!\n";
          goto dlab;
        }
        r->addItem(inv[--ini]); // Add the item to the room 
        inv.erase(inv.begin() + ini);
        break;
      }
      if (inc == 'm') {
      mlab:
	cout << "Enter the exit you want to go to (N, S, E, W): ";
	cin >> inc;
	cin.ignore();
	inc = tolower(inc);
	Room* nr = r->getRoomFromExitChar(inc);
	if (nr == nullptr) {
	  cout << "There is no such available room!\n";
	  goto mlab;
	}
	r = nr;
	break;
      }
      cout << "Invalid option!\n";
    }
  }
  return 0;
}
