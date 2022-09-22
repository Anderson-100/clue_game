#include <stddef.h>
#include <stdio.h>

#include "avatar.h"

struct Item* getInventory(struct User* user) {
  return user->inventory;
}

void setInventory(struct User* user, struct Item* itemList) {
  if (itemList != NULL)
    user->inventory = itemList;
}

void setUserLocation(struct User* user, struct Room* room) {
  if (room != NULL) {
    user->location = room;
  }
}

void setCharLocation(struct Character* c, struct Room* room) {
  if (room != NULL) {
    c->location = room;
  }
}

struct Room* getCharLocation(struct Character* c) {
  if (c != NULL) {
    return c->location;
  }
}

void printCharacters(struct Character* charList) {
  printf("Characters:\n");
  while (charList != NULL) {
    printf("  %s\n", charList->name);
    charList = charList->next;
  }
}