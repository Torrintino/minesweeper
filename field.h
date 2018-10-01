#ifndef FIELD_H
#define FIELD_H

#include "minesweeper.h"

int ROWS;
int COLS;
int MINE_COUNT;

// Counts how many points have been revealed in the game
// Used to determine, when the player has won
int REVEALED_POINTS;

// Counts how many mines have yet to be marked
int UNMARKED_MINES;

// Datastructure for the precomputed playfield
char** field;
// Datastructure for the status of each point
int** status;

#define STATE_UNREVEALED 0
#define STATE_REVEALED 1
#define STATE_MARKED 2


// Foreground ANSI Color Codes
#define FG_BLACK "\x1b[30m"
#define FG_RED "\x1b[31m"
#define FG_GREEN "\x1b[32m"
#define FG_YELLOW "\x1b[33m"
#define FG_BLUE "\x1b[34m"
#define FG_MAGENTA "\x1b[35m"
#define FG_CYAN "\x1b[36m"
#define FG_WHITE "\x1b[37m"
#define FG_BRIGHT_BLACK "\x1b[90m"
#define FG_BRIGHT_RED "\x1b[91m"
#define FG_BRIGHT_GREEN "\x1b[92m"
#define FG_BRIGHT_YELLOW "\x1b[93m"
#define FG_BRIGHT_BLUE "\x1b[94m"
#define FG_BRIGHT_MAGENTA "\x1b[95m"
#define FG_BRIGHT_CYAN "\x1b[96m"
#define FG_BRIGHT_WHITE "\x1b[97m"

// Background ANSI Color Codes
#define BG_BLACK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN "\x1b[46m"
#define BG_WHITE "\x1b[47m"
#define BG_BRIGHT_BLACK "\x1b[100m"
#define BG_BRIGHT_RED "\x1b[101m"
#define BG_BRIGHT_GREEN "\x1b[102m"
#define BG_BRIGHT_YELLOW "\x1b[103m"
#define BG_BRIGHT_BLUE "\x1b[104m"
#define BG_BRIGHT_MAGENTA "\x1b[105m"
#define BG_BRIGHT_CYAN "\x1b[106m"
#define BG_BRIGHT_WHITE "\x1b[107m"

void set_size(int rows, int columns, int mine_count);
int init_field();
void destroy_field();

int is_mine(int i, int j);
int mark_mine(int i, int j);
int reveal_point(int i, int j);

#endif
