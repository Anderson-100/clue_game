// #include "items.h"

struct Room {
  char* name;
  struct Room* North;
  struct Room* South;
  struct Room* East;
  struct Room* West;
  struct Item* itemList;
  struct Character* characters;
};

// struct Room* createRoom(char* name);

// void freeRoom(struct Room* room);

char* getRoomName(struct Room* room);

struct Room* getNorth(struct Room* room);

struct Room* getSouth(struct Room* room);

struct Room* getEast(struct Room* room);

struct Room* getWest(struct Room* room);

// Print out North, South, East, and West rooms
// with respect to inputted room.
void printNeighbors(struct Room* room);

struct Item* getItemList(struct Room* room);

void setItemList(struct Room* room, struct Item* itemList);

void setNorth(struct Room* room, struct Room* north);

void setSouth(struct Room* room, struct Room* south);

void setEast(struct Room* room, struct Room* east);

void setWest(struct Room* room, struct Room* west);

int itemInRoom(struct Room* room, char* itemName);

struct Character* getCharacterList(struct Room* room);

int characterInRoom(struct Room* room, char* charName);

void addCharacter(struct Room* room, struct Character* c);

struct Character* deleteCharacter(struct Room* room, char* name);