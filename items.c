#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "items.h"

struct Item* add_item(struct Item* list, struct Item* newItem) {
  // Length = 0
  if (list == NULL) {
    return newItem;
  }

  // Length >= 1
  while (list->next != NULL) {
    list = list->next;
  }
  list->next = newItem;

  return list;
}

struct Item* drop_item(struct Item* list, char* itemName) {
  // Length 0 - nothing to drop
  if (list == NULL) {
    return NULL;
  }

  // Length = 1
  struct Item* curItem = list;
  if (curItem->next == NULL) {
    if (strcmp(curItem->name, itemName) == 0) {
      return NULL;
    }
  }

  // Length >= 2
  while (curItem->next != NULL) {
    struct Item* nextItem = curItem->next;
    if (strcmp(curItem->name, itemName) == 0) {
      curItem->next = nextItem->next;
      return list;
    }
  }

  return list;
}

struct Item* findItem(struct Item* list, char* itemName) {
  if (list == NULL) {
    return NULL;
  }
  
  while (list != NULL) {
    if (strcmp(list->name, itemName) == 0) {
      return list;
    }
    list = list->next;
  }
  return NULL;
}

void printItems(struct Item* itemList) {
  printf("Items:\n");
  while (itemList != NULL) {
    printf("  %s\n", itemList->name);
    itemList = itemList->next;
  }
}