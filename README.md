# Project 01 - Clue
### CS 230
### Author: Anderson Hsiao

This program is a simplified, single-player, text-based adventure game version of the board game Clue. 

The game board consists of 9 `Room` data structures, which are set up in a 3x3 grid and connected to each other via pointers. These pointers are used to efficiently access data about neighboring rooms and to actually move to those rooms.

The game flows through text inputs by the user. When prompted to enter text, the user can enter any of the available commands or type `help` to see a list of all the commands. The inputs are saved into variables, which are then processed so that the program can react accordingly.

The `adventure.c` file is set up so that it contains almost does not directly deal with pointers at all; most of that is abstracted away into the other files for better readability. 

The `adventure.c` file can be divided into 3 main parts:
1. The setup part. This is where all the rooms, characters, and items are set up in preparation for the game. This starts at line 14 and ends at line 162.
2. The commands part. This is a long list of if statements contained within a while loop, each of which deals with one of the specified commands. This starts at line 166 and ends at line 447.
3. The free part. This is the end of the game. I tell the user the result of their game, and free all of the memory I had allocated when initializing the game. This goes from line 450 to the end of the file.

How to compile:
`gcc adventure.c rooms.c items.c avatar.c`

Additional Files:
- `answer.h`: Header file containing struct for storing the correct room, item, and character of each game, all of which are stored as strings.
- `avatar.h`: Header file containting struct for the user, and a struct representing the 5 computer characters in the game. 
  - The `User` struct contains a pointer to a linked list of `Item` structs representing their inventory and a pointer to a `Room` struct to keep track of which room the user is in. 
  - The `Character` struct contains the character's name, a pointer to the `Room` they're in, and a pointer to a "next" `Character` so it can be implemented as a linked list.
- `avatar.c`: File containing functions for accessing and manipulating values in both the `User` and `Character` structs.
