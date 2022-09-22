#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "rooms.h"
#include "avatar.h"
#include "items.h"

char* getRoomName(struct Room* room) {
  return room->name;
}

struct Room* getNorth(struct Room* room) {
  return room->North;
}

struct Room* getSouth(struct Room* room) {
  return room->South;
}

struct Room* getEast(struct Room* room) {
  return room->East;
}

struct Room* getWest(struct Room* room) {
  return room->West;
}

void printNeighbors(struct Room* room) {
  struct Room* north = getNorth(room);
  char* northName = (north == NULL) ? "" : getRoomName(north);
  printf("North: %s\n", northName);

  struct Room* south = getSouth(room);
  char* southName = (south == NULL) ? "" : getRoomName(south);
  printf("South: %s\n", southName);

  struct Room* east = getEast(room);
  char* eastName = (east == NULL) ? "" : getRoomName(east);
  printf("East:  %s\n", eastName);

  struct Room* west = getWest(room);
  char* westName = (west == NULL) ? "" : getRoomName(west);
  printf("West:  %s\n", westName);
}

struct Item* getItemList(struct Room* room) {
  return room->itemList;
}

void setItemList(struct Room* room, struct Item* itemList) {
  room->itemList = itemList;
}

void setNorth(struct Room* room, struct Room* north) {
  room->North = north;
}

void setSouth(struct Room* room, struct Room* south) {
  room->South = south;
}

void setEast(struct Room* room, struct Room* east) {
  room->East = east;
}

void setWest(struct Room* room, struct Room* west) {
  room->West = west;
}

int itemInRoom(struct Room* room, char* itemName) {
  // Length = 0 (to prevent segmentation fault)
  if (room->itemList == NULL) {
    return 0;
  }

  // Length > 0
  struct Item* curItem = room->itemList;

  while (curItem != NULL) {
    if (strcmp(curItem->name, itemName) == 0) {
      return 1;
    }
    curItem = curItem->next;
  }
  return 0;
}

struct Character* getCharacterList(struct Room* room) {
  return room->characters;
}

int characterInRoom(struct Room* room, char* charName) {
  // Length = 0 (to prevent segmentation fault)
  if (room->characters == NULL) {
    return 0;
  }

  // Length > 0
  struct Character* curChar = room->characters;

  while (curChar != NULL) {
    if (strcmp(curChar->name, charName) == 0) {
      return 1;
    }
    curChar = curChar->next;
  }
  return 0;
}

void addCharacter(struct Room* room, struct Character* c) {
  // Length = 0 (to prevent segmentation fault)
  if (room->characters == NULL) {
    room->characters = c;
    return;
  }

  // Length > 0
  struct Character* curChar = room->characters;

  while (curChar->next != NULL) {
    if (strcmp(curChar->name, c->name) == 0) {
      return;
    }
    curChar = curChar->next;
  }
  curChar->next = c;
}

struct Character* deleteCharacter(struct Room* room, char* name) {
  // Length = 0 (to prevent segmentation fault)
  if (room->characters == NULL) {
    return NULL;
  }

  // Length = 1
  if (strcmp(room->characters->name, name) == 0) {
    struct Character* toDelete = room->characters;
    room->characters = NULL;
    return toDelete;
  }

  // Length > 1
  struct Character* curChar = room->characters;

  while (curChar->next != NULL) {
    struct Character* nextChar = curChar->next;
    if (strcmp(curChar->name, name) == 0) {
      struct Character* toDelete = curChar->next;
      curChar->next = nextChar->next;
      return toDelete;
    }
  }
  return NULL;
}