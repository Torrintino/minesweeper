#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "field.h"


void set_size(int rows, int columns, int mine_count) {
  ROWS = rows;
  COLS = columns;
  MINE_COUNT = mine_count;
  
  // The first rows displays coordinates, the second is a separator
  VFIELD_ROWS = rows + 2;
  
  // Before each point is one whitespace
  // The first column contains coordinates
  // The second column is a separator
  // The last column contains \0 terminators for each line
  VFIELD_COLS = 2 * columns + 3;
}

int init_vfield() {
  vfield = malloc(sizeof(char*) * VFIELD_ROWS);
  if(vfield == NULL) return 0;
  for(int i=0; i<VFIELD_ROWS; i++) {
    vfield[i] = malloc(sizeof(char) * VFIELD_COLS);
    if(vfield[i] == NULL) return 0;
  }
  
  vfield[0][0] = ' ';
  vfield[0][1] = ' ';

  // Set first row with coordinates
  for(int i=2; i<VFIELD_COLS-2; i+=2) {
    vfield[0][i] = ' ';
    vfield[0][i+1] = '0' + (((i - 1) / 2) + 1) % 10;
  }

  // Set second row to blank
  for(int i=0; i<VFIELD_COLS-1; i++)
    vfield[1][i] = '_';

  // Other rows
  for(int i=2;i<VFIELD_ROWS;i++) {
    // Set first two columns to coordinates
    vfield[i][0] = '0' + ((i - 1)) % 10;
    vfield[i][1] = '|';

    // Set other columns with blanks and place holders
    for(int j=2;j<VFIELD_COLS-2; j+=2) {
      vfield[i][j] = ' ';
      vfield[i][j+1] = '-';
    }

    // Set null byte for each line
    for(int i=0; i<VFIELD_ROWS; i++)
      vfield[i][VFIELD_COLS - 1] = '\0';
  }

  return 1;
}

void print_vfield() {
  for(int i=0;i<VFIELD_ROWS;i++)
    printf("%s\n", vfield[i]);
}

int is_mine(int i, int j) {
  return hfield[i][j] == '*';
}

int init_hfield(int row, int column) {
  hfield = malloc(sizeof(char*) * ROWS);
  if(hfield == NULL) return 0;
  for(int i=0; i<ROWS; i++) {
    hfield[i] = malloc(sizeof(char) * COLS);
    if(hfield == NULL) return 0;
  }
  
  // Make every point empty
  for(int i=0; i<ROWS; i++) {
    for(int j=0; j<COLS; j++) {
      hfield[i][j] = ' ';
    }
  }

  // Randomly put mines
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i < MINE_COUNT;) {
    int x = rand() % ROWS;
    int y = rand() % COLS;
    if(hfield[x][y] != '*' && !(x == row && y == column)) {
      hfield[x][y] = '*';
      i++;
    }
  }

  // Calculate point numbers
  for(int i=0; i<ROWS; i++) {
    for(int j=0; j<COLS; j++) {
      if(hfield[i][j] == '*')
	continue;
      hfield[i][j] = '0';

      // top left
      if(i != 0 && j != 0) {
	if(is_mine(i-1, j-1))
	  hfield[i][j]++;
      }

      // top
      if(i != 0) {
	if(is_mine(i-1, j))
	  hfield[i][j]++;
      }

      // top right
      if(i != 0 && j != COLS-1) {
	if(is_mine(i-1, j+1))
	  hfield[i][j]++;
      }

      // left
      if(j != 0) {
	if(is_mine(i, j-1))
	  hfield[i][j]++;
      }

      // right
      if(j != COLS-1) {
	if(is_mine(i, j+1))
	  hfield[i][j]++;
      }

      // bottom left
      if(i != ROWS-1 && j != 0) {
	if(is_mine(i+1, j-1))
	  hfield[i][j]++;
      }

      // bottom
      if(i != ROWS-1) {
	if(is_mine(i+1, j))
	  hfield[i][j]++;
      }

      // bottom right
      if(i != ROWS-1 && j != COLS-1) {
	if(is_mine(i+1, j+1))
	  hfield[i][j]++;
      }

      if(hfield[i][j] == '0')
	hfield[i][j] = ' ';
    }
  }

  return 1;
}

void print_hfield() {
  for(int i=0; i<ROWS; i++) {
    for(int j=0; j<COLS; j++) {
      printf("%c ", hfield[i][j]);
    }
    printf("\n");
  }
}

int get_column(int i) {
  return i * 2 + 3;
}

int get_row(int i) {
  return i + 2;
}

// Return True if mine was revealed
int reveal_point(int i, int j) {
  if(vfield[get_row(i)][get_column(j)] != '-')
    return 0;
  REVEALED_POINTS++;
  vfield[get_row(i)][get_column(j)] = hfield[i][j];
  // Recursively 
  if(hfield[i][j] == ' ') {
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
  return hfield[i][j] == '*';
}

int mark_mine(int i, int j) {
  int r = get_row(i), c = get_column(j);
  if(vfield[r][c] == '*') {
    vfield[r][c] = '-';
    return 0;
  }
  
  if(vfield[r][c] != '-')
    return -1;
  vfield[r][c] = '*';
  return 1;
}

void destroy_vfield() {
  for(int i=0; i<VFIELD_ROWS;i++)
    free(vfield[i]);
  free(vfield);
}

void destroy_hfield() {
  for(int i=0; i<ROWS;i++)
    free(hfield[i]);
  free(hfield);
}
