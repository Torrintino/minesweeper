#ifndef FIELD_H
#define FIELD_H

#include "minesweeper.h"

int ROWS;
int COLS;
int VFIELD_ROWS;
int VFIELD_COLS;
int MINE_COUNT;

// Counts how many points have been revealed in the game
// Used to determine, when the player has won
int REVEALED_POINTS;

// hidden, used for initialization and lookup
char** hfield;

// visible, used for displaying the current game state
// note that the coordinates go from 1 - FIELD_SIZE
// however the coordinates need to decreased by one, as
// hfield has coordinates from 0 - (FIELD_SIZE-1)
char** vfield;

void set_size(int rows, int columns, int mine_count);
int init_vfield();
void print_vfield();
int init_hfield();
void destroy_vfield();
void destroy_hfield();

int is_mine(int i, int j);
int mark_mine(int i, int j);
int reveal_point(int i, int j);

#endif
