#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "field.h"


void set_size(int rows, int columns, int mine_count) {
  ROWS = rows;
  COLS = columns;
  MINE_COUNT = mine_count;
  UNMARKED_MINES = mine_count;
}

int is_mine(int i, int j) {
  return field[i][j] == '*';
}

int init_field(int row, int column) {
  field = malloc(sizeof(char*) * ROWS);
  if(field == NULL) return 0;
  for(int i=0; i<ROWS; i++) {
    field[i] = malloc(sizeof(char) * COLS);
    if(field == NULL) return 0;
    for(int j=0; j<COLS; j++)
      field[i][j] = ' ';
  }

  status = malloc(sizeof(int*) * ROWS);
  if(status == NULL) return 0;
  for(int i=0; i<ROWS; i++) {
    status[i] = malloc(sizeof(int) * COLS);
    if(status == NULL) return 0;
    for(int j=0; j<COLS; j++)
      status[i][j] = 0;
  }

  // Randomly put mines
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i < MINE_COUNT;) {
    int x = rand() % ROWS;
    int y = rand() % COLS;
    if(field[x][y] != '*' && !(x == row && y == column)) {
      field[x][y] = '*';
      i++;
    }
  }

  // Calculate point numbers
  for(int i=0; i<ROWS; i++) {
    for(int j=0; j<COLS; j++) {
      if(field[i][j] == '*')
	continue;
      field[i][j] = '0';

      // top left
      if(i != 0 && j != 0) {
	if(is_mine(i-1, j-1))
	  field[i][j]++;
      }

      // top
      if(i != 0) {
	if(is_mine(i-1, j))
	  field[i][j]++;
      }

      // top right
      if(i != 0 && j != COLS-1) {
	if(is_mine(i-1, j+1))
	  field[i][j]++;
      }

      // left
      if(j != 0) {
	if(is_mine(i, j-1))
	  field[i][j]++;
      }

      // right
      if(j != COLS-1) {
	if(is_mine(i, j+1))
	  field[i][j]++;
      }

      // bottom left
      if(i != ROWS-1 && j != 0) {
	if(is_mine(i+1, j-1))
	  field[i][j]++;
      }

      // bottom
      if(i != ROWS-1) {
	if(is_mine(i+1, j))
	  field[i][j]++;
      }

      // bottom right
      if(i != ROWS-1 && j != COLS-1) {
	if(is_mine(i+1, j+1))
	  field[i][j]++;
      }

      if(field[i][j] == '0')
	field[i][j] = ' ';
    }
  }

  return 1;
}

/* For given x coordinate of a point,
   return the according x coordinate of that point on the screen
*/
int get_column(int i) {
  return i * 2 + 4;
}

/* For given y coordinate of a point,
   return the according y coordinate of that point on the screen
*/
int get_row(int i) {
  return i + 5;
}

// Return True if mine was revealed
int reveal_point(int i, int j) {
  if(status[i][j] != STATE_UNREVEALED)
    return 0;
  REVEALED_POINTS++;
  status[i][j] = STATE_REVEALED;
  printf("\e[%d;%dH%c", get_row(i), get_column(j), field[i][j]);
  // Recursively 
  if(field[i][j] == ' ') {
    // top left
    if(i != 0 && j != 0) reveal_point(i-1, j-1);
    // top
    if(i != 0) reveal_point(i-1, j);
    // top right
    if(i != 0 && j != COLS-1) reveal_point(i-1, j+1);
    // left
    if(j != 0) reveal_point(i, j-1);
    // right
    if(j != COLS-1) reveal_point(i, j+1);
    // bottom left
    if(i != ROWS-1 && j != 0) reveal_point(i+1, j-1);
    // bottom
    if(i != ROWS-1) reveal_point(i+1, j);
    // bottom right
    if(i != ROWS-1 && j != COLS-1) reveal_point(i+1, j+1);
  }
  return field[i][j] == '*';
}

/* Returns 0, if a point got unmarked
   Returns 1, if a point got marked
   Returns -1, if the point was already revealed
 */
int mark_mine(int i, int j) {
  if(status[i][j] == STATE_UNREVEALED) {
    status[i][j] = STATE_MARKED;
    printf("\e[%d;%dH*", get_row(i), get_column(j));
    UNMARKED_MINES--;
    printf("\e[1;13H%d  ", UNMARKED_MINES);
    return 1;
  }
  if(status[i][j] == STATE_MARKED) {
    status[i][j] = STATE_UNREVEALED;
    printf("\e[%d;%dH-", get_row(i), get_column(j));
    UNMARKED_MINES++;
    printf("\e[1;13H%d  ", UNMARKED_MINES);
    return 0;
  }
  return -1;
}

void destroy_field() {
  for(int i=0; i<ROWS;i++)
    free(field[i]);
  free(field);

  for(int i=0; i<ROWS;i++)
    free(status[i]);
  free(status);
}

