#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "items.h"
#include "rooms.h"
#include "avatar.h"
#include "answer.h"

int main() {

  // Initialize random funciton
  srand(time(NULL));

  // Initialize player names
  char * names[5];
  names[0] = "Mustard";
  names[1] = "Plum";
  names[2] = "White";
  names[3] = "Scarlet";
  names[4] = "Green";

  // Initialize item names
  char * items[9];
  items[0] = "candlestick";
  items[1] = "knife";
  items[2] = "lead_pipe";
  items[3] = "revolver";
  items[4] = "rope";
  items[5] = "wrench";
  items[6] = "";
  items[7] = "";
  items[8] = "";

  // Initialize room names
  char * rooms[9];
  rooms[0] = "kitchen";
  rooms[1] = "ballroom";
  rooms[2] = "conservatory";
  rooms[3] = "dining_room";
  rooms[4] = "billiard_room";
  rooms[5] = "library";
  rooms[6] = "lounge";
  rooms[7] = "hall";
  rooms[8] = "study";

  // Create a random answer
  struct Answer answer = {
    rooms[rand() % 9],
    items[rand() % 6],
    names[rand() % 5]
  };

  printf("%s\n", answer.room);
  printf("%s\n", answer.item);
  printf("%s\n", answer.name);

  // Initialize Rooms
  struct Room* a0 = malloc(sizeof(struct Room));
  struct Room* a1 = malloc(sizeof(struct Room));
  struct Room* a2 = malloc(sizeof(struct Room));
  struct Room* b0 = malloc(sizeof(struct Room));
  struct Room* b1 = malloc(sizeof(struct Room));
  struct Room* b2 = malloc(sizeof(struct Room));
  struct Room* c0 = malloc(sizeof(struct Room));
  struct Room* c1 = malloc(sizeof(struct Room));
  struct Room* c2 = malloc(sizeof(struct Room));

  struct Room* roomsArr[3][3] = {{a0, a1, a2}, {b0, b1, b2}, {c0, c1, c2}};

  // Connect rooms
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i > 0) {
        roomsArr[i][j]->North = roomsArr[i-1][j];
      }
      if (i < 2) {
        roomsArr[i][j]->South = roomsArr[i+1][j];
      }
      if (j > 0) {
        roomsArr[i][j]->West = roomsArr[i][j-1];
      }
      if (j < 2) {
        roomsArr[i][j]->East = roomsArr[i][j+1];
      }
    }
  }

  // Shuffle the room and item names
  for (int i = 0; i < 9; i++) {
    int randNum = rand() % 9;
    // printf("%i\n", randNum);
    char* temp = rooms[i];
    rooms[i] = rooms[randNum];
    rooms[randNum] = temp;

    randNum = rand() % 9;
    temp = items[i];
    items[i] = items[randNum];
    items[randNum] = temp;
  }

  // Save items to array (to free later)
  struct Item* itemStructs[6];
  int cnt = 0;

  // Assign room names and items
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {

      // Set room name
      roomsArr[i][j]->name = rooms[3*i + j];
      // printf("%s\n", roomsArr[i][j]->name);
      
      char* itemName = items[3*i + j];
      if (strcmp(itemName, "") != 0) {
        // Set first item
        struct Item* newItem = malloc(sizeof(struct Item));
        newItem->name = itemName;
        itemStructs[cnt++] = newItem;
        struct Item* list = add_item(roomsArr[i][j]->itemList, newItem);
        roomsArr[i][j]->itemList = list;
      }
    }
  }

  struct Character* ch0 = malloc(sizeof(struct Character));
  ch0->name = names[0];
  struct Character* ch1 = malloc(sizeof(struct Character));
  ch1->name = names[1];
  struct Character* ch2 = malloc(sizeof(struct Character));
  ch2->name = names[2];
  struct Character* ch3 = malloc(sizeof(struct Character));
  ch3->name = names[3];
  struct Character* ch4 = malloc(sizeof(struct Character));
  ch4->name = names[4];

  struct Character* chars[] = { ch0, ch1, ch2, ch3, ch4 };

  // Assign characters to rooms
  for (int i = 0; i < 5; i++) {
    int roomNum = rand() % 9;
    // Initialize character struct
    struct Character* c = chars[i];
    struct Room* r = roomsArr[roomNum / 3][roomNum % 3];
    addCharacter(r, c);
    setCharLocation(c, r);
  }



  // Initialize user
  struct User* user = malloc(sizeof(struct User));

  // Pick a random room for the user to start in
  int randRoom = rand() % 9;
  struct Room* curRoom = roomsArr[randRoom / 3][randRoom % 3];
  setUserLocation(user, curRoom);

  printf("Welcome, Player.\n");
  printf("You are in the %s.\n", curRoom->name);

  // Gameplay starts here

  int loop = 1;
  int win = 0;
  int attempts = 0;
  while (loop) {
    char command[20];
    printf("Enter command: ");
    scanf("%19s", command);

    // help
    if (strcmp("help", command) == 0) {
      printf("help:      look up all commands\n");
      printf("list:      list all the rooms, items, and characters\n");
      printf("look:      get information about your current room\n");
      printf("go:        move to another room\n");
      printf("take:      add an item to your inventory\n");
      printf("drop:      remove an item from your inventory\n");
      printf("inventory: look at your inventory\n");
      printf("clue:      make a guess\n");
    }

    // list
    else if (strcmp("list", command) == 0) {
      printf("Characters: Mustard\n");
      printf("            Green\n");
      printf("            White\n");
      printf("            Plum\n");
      printf("            Scarlet\n");

      printf("Items: candlestick\n");
      printf("       knife\n");
      printf("       lead_pipe\n");
      printf("       revolver\n");
      printf("       rope\n");
      printf("       wrench\n");

      printf("Rooms: kitchen\n");
      printf("       ballroom\n");
      printf("       conservatory\n");
      printf("       dining_room\n");
      printf("       billiard_room\n");
      printf("       library\n");
      printf("       lounge\n");
      printf("       hall\n");
      printf("       study\n");
    }

    // look
    else if (strcmp("look", command) == 0) {
      printf("Current Room: %s\n", getRoomName(curRoom));
      printNeighbors(curRoom);
      printCharacters(getCharacterList(curRoom));
      printItems(getItemList(curRoom));
    }

    // go
    else if (strcmp("go", command) == 0) {
      char dir[6];
      int innerLoop = 1;
      while (innerLoop) {
        printf("Direction: ");
        scanf("%5s", dir);

        if (strcmp("north", dir) == 0) {
          if (getNorth(curRoom) != NULL) {
            curRoom = getNorth(curRoom);
            innerLoop = 0;
          }
          else {
            printf("You cannot go north.\n");
          }
        }
        else if (strcmp("south", dir) == 0) {
          if (getSouth(curRoom) != NULL) {
            curRoom = getSouth(curRoom);
            innerLoop = 0;
          }
          else {
            printf("You cannot go sorth.\n");
          }
        }
        else if (strcmp("east", dir) == 0) {
          if (getEast(curRoom) != NULL) {
            curRoom = getEast(curRoom);
            innerLoop = 0;
          }
          else {
            printf("You cannot go east.\n");
          }
        }
        else if (strcmp("west", dir) == 0) {
          if (getWest(curRoom) != NULL) {
            curRoom = getWest(curRoom);
            innerLoop = 0;
          }
          else {
            printf("You cannot go west.\n");
          }
        }
        else if (strcmp("back", dir) == 0) {
          break;
        }
        else {
          printf("Direction not recognized. Please try again (type in all lowercase).\n");
        }
      }
      printf("You are now in %s.\n", getRoomName(curRoom));
      setUserLocation(user, curRoom);
    }

    // take
    else if (strcmp("take", command) == 0) {
      if (getItemList(curRoom) == NULL) {
        printf("There are no items in this room to take.\n");
        continue;
      }

      char input[20];
      int innerLoop = 1;
      while (innerLoop) {
        printf("Item: ");
        scanf("%19s", input);

        if (strcmp("back", input) == 0) {
          break;
        }

        struct Item* droppedItem = findItem(getItemList(curRoom), input);
        if (droppedItem != NULL) {
          struct Item* roomList = drop_item(getItemList(curRoom), input);
          setItemList(curRoom, roomList);
          struct Item* userList = add_item(getInventory(user), droppedItem);
          setInventory(user, userList);

          printf("%s added to your inventory.\n", input);

          innerLoop = 0;
        }
        else {
          printf("The %s is not in this room.\n", input);
        }
      }
    }

    // drop
    else if (strcmp("drop", command) == 0) {
      if (getInventory(user) == NULL) {
        printf("There are no items in your inventory to drop.\n");
        continue;
      }

      char input[20];
      int innerLoop = 1;
      while (innerLoop) {
        printf("Item: ");
        scanf("%19s", input);

        if (strcmp("back", input) == 0) {
          break;
        }

        struct Item* droppedItem = findItem(getInventory(user), input);
        if (droppedItem != NULL) {
          struct Item* userList = drop_item(getInventory(user), input);
          setInventory(user, userList);
          struct Item* roomList = add_item(getItemList(curRoom), droppedItem);
          setItemList(curRoom, roomList);

          printf("%s dropped from your inventory.\n", input);

          innerLoop = 0;
        }
        else {
          printf("The %s is not in your inventory.\n", input);
        }
      }
    }

    // inventory
    else if (strcmp("inventory", command) == 0) {
      printItems(getInventory(user));
    }

    // clue
    else if (strcmp("clue", command) == 0) {

      // If the room doesn't have any items
      // or the user's inventory is empty,
      // don't let them guess.
      if (getItemList(curRoom) == NULL && getInventory(user) == NULL) {
        printf("You cannot use the clue command right now because there are no items in your room or inventory.\n");
        continue;
      }

      char charGuess[20];
      int charLoop = 1;
      struct Character* charStruct;

      while (charLoop) {
        printf("Character: ");
        scanf("%19s", charGuess);

        for (int i = 0; i < 5; i++) {
          if (strcmp(chars[i]->name, charGuess) == 0) {
            charStruct = chars[i];
            charLoop = 0;
            break;
          }
        }

        if (charLoop) {
          printf("%s is not a valid character name. Try again.\n", charGuess);
        }
      }
      
      char itemGuess[20];
      int itemLoop = 1;
      while (itemLoop) {
        printf("Item: ");
        scanf("%19s", itemGuess);

        // Check if in user list or room list
        struct Item* itemFromRoom = findItem(getItemList(curRoom), itemGuess);
        struct Item* itemFromUser = findItem(getInventory(user), itemGuess);
        
        if (itemFromRoom == NULL && itemFromUser == NULL) {
          printf("%s is not in the current room or your inventory. Try again.\n", itemGuess);
        }
        else {
          itemLoop = 0;
        }
      }

      // TODO: Move character to current room
      struct Room* charRoom = getCharLocation(charStruct);
      
      if (charRoom != curRoom) {
        deleteCharacter(charRoom, charGuess);
        addCharacter(curRoom, charStruct);
      }

      int roomMatch = 0;
      int charMatch = 0;
      int itemMatch = 0;

      if (strcmp(getRoomName(curRoom), answer.room) == 0) {
        printf("Room Match\n");
        roomMatch = 1;
      }
      if (strcmp(charGuess, answer.name) == 0) {
        printf("Character Match\n");
        charMatch = 1;
      }
      if (strcmp(itemGuess, answer.item) == 0) {
        printf("Item Match\n");
        itemMatch = 1;
      }

      if (roomMatch && charMatch && itemMatch) {
        win = 1;
        loop = 0;
      }
      else {
        printf("Incorrect. Attempts left: %i\n", (10-attempts-1));
      }

      if (++attempts >= 10) {
        loop = 0;
      }
    }
    
    // Typo
    else {
      printf("The %s command does not exist. Use \"help\" for the list of all commands.\n", command);
    }
  }

  if (win) {
    printf("Congratulations! You got the answer in %i tries.\n", attempts);
  }
  else {
    printf("You have used up all of your 10 attempts. Better luck next time!\n");
  }


  // Free memory
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      free(roomsArr[i][j]);
    }
  }
  for (int i = 0; i < 6; i++) {
    free(itemStructs[i]);
  }
  for (int i = 0; i < 5; i++) {
    free(chars[i]);
  }

  free(user);
}
