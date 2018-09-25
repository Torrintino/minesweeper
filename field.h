#ifndef FIELD_H
#define FIELD_H

#include "minesweeper.h"

// hidden, used for initialization and lookup
char hfield[FIELD_SIZE][FIELD_SIZE];

// The first rows displays coordinates, the second is a separator
#define VFIELD_ROWS FIELD_SIZE + 2

// Before each point is one whitespace
// The first column contains coordinates
// The second column is a separator
// The last column contains \0 terminators for each line
#define VFIELD_COLUMNS 2 * FIELD_SIZE + 3

// visible, used for displaying the current game state
// note that the coordinates go from 1 - FIELD_SIZE
// however the coordinates need to decreased by one, as
// hfield has coordinates from 0 - (FIELD_SIZE-1)
char vfield[VFIELD_ROWS][VFIELD_COLUMNS];

// Counts how many points have been revealed in the game
// Used to determine, when the player has won
int REVEALED_POINTS;

void init_vfield();
void print_vfield();
void init_hfield();

int is_mine(int i, int j);
void mark_mine(int i, int j);
int reveal_point(int i, int j);

// rand creates a random numver
// rand_mine translates such a number into a valid coordinate
int rand();
int rand_mine();

#endif
