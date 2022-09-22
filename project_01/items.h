struct Item {
  char* name;
  struct Item* next;
};

/*
 * Adds an item to the given linked list of items.
 * Returns linked list with the new item added.
*/
struct Item* add_item(struct Item* list, struct Item* newItem);

/*
 * Removes an item from the given linked list of items.
 * Returns the removed item, NULL if nothing was removed.
*/
struct Item* drop_item(struct Item* list, char* itemName);

/*
 * Finds an item within a linked list and returns it.
 * Returns the item if found, NULL if not.
*/
struct Item* findItem(struct Item* list, char* itemName);

/*
 * Prints out the names of all the items within a given list.
*/
void printItems(struct Item* itemList);