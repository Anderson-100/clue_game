// User player
struct User {
  struct Item* inventory;
  struct Room* location;
};

// Linked list of characters
struct Character {
  char* name;
  struct Room* location;
  struct Character* next;
};

struct Item* getInventory(struct User* user);

void setInventory(struct User* user, struct Item* itemList);

void setUserLocation(struct User* user, struct Room* room);

void setCharLocation(struct Character* c, struct Room* room);

struct Room* getCharLocation(struct Character* c);

void printCharacters(struct Character* charList);