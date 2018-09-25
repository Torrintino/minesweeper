#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "field.h"

void init_vfield() {
  vfield[0][0] = ' ';
  vfield[0][1] = ' ';

  // Set first row with coordinates
  for(int i=2; i<VFIELD_COLUMNS-2; i+=2) {
    vfield[0][i] = ' ';
    vfield[0][i+1] = '0' + ((i - 1) / 2) + 1;
  }

  // Set second row to blank
  for(int i=0; i<VFIELD_COLUMNS-1; i++)
    vfield[1][i] = '_';

  // Other rows
  for(int i=2;i<VFIELD_ROWS;i++) {
    // Set first two columns to coordinates
    vfield[i][0] = '0' + (i - 1);
    vfield[i][1] = '|';

    // Set other columns with blanks and place holders
    for(int j=2;j<VFIELD_COLUMNS-2; j+=2) {
      vfield[i][j] = ' ';
      vfield[i][j+1] = '-';
    }

    // Set null byte for each line
    for(int i=0; i<VFIELD_ROWS; i++)
      vfield[i][VFIELD_COLUMNS - 1] = '\0';
  }
}

void print_vfield() {
  for(int i=0;i<VFIELD_ROWS;i++)
    printf("%s\n", vfield[i]);
}

int is_mine(int i, int j) {
  return hfield[i][j] == '*';
}

void init_hfield() {
  // Make every point empty
  for(int i=0; i<FIELD_SIZE; i++) {
    for(int j=0; j<FIELD_SIZE; j++) {
      hfield[i][j] = ' ';
    }
  }

  // Randomly put mines
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i < MINE_COUNT; i++) {
    int x = rand() % FIELD_SIZE;
    int y = rand() % FIELD_SIZE;
    if(hfield[x][y] == '*') {
      i--;
    } else {
      hfield[x][y] = '*';
    }
  }

  // Calculate point numbers
  for(int i=0; i<FIELD_SIZE; i++) {
    for(int j=0; j<FIELD_SIZE; j++) {
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
      if(i != 0 && j != FIELD_SIZE-1) {
	if(is_mine(i-1, j+1))
	  hfield[i][j]++;
      }

      // left
      if(j != 0) {
	if(is_mine(i, j-1))
	  hfield[i][j]++;
      }

      // right
      if(j != FIELD_SIZE-1) {
	if(is_mine(i, j+1))
	  hfield[i][j]++;
      }

      // bottom left
      if(i != FIELD_SIZE-1 && j != 0) {
	if(is_mine(i+1, j-1))
	  hfield[i][j]++;
      }

      // bottom
      if(i != FIELD_SIZE-1) {
	if(is_mine(i+1, j))
	  hfield[i][j]++;
      }

      // bottom right
      if(i != FIELD_SIZE-1 && j != FIELD_SIZE-1) {
	if(is_mine(i+1, j+1))
	  hfield[i][j]++;
      }
    }
  }
}

void print_hfield() {
  for(int i=0; i<FIELD_SIZE; i++) {
    for(int j=0; j<FIELD_SIZE; j++) {
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
  if(hfield[i][j] == '0') {
    // top left
    if(i != 0 && j != 0) reveal_point(i-1, j-1);
    // top
    if(i != 0) reveal_point(i-1, j);
    // top right
    if(i != 0 && j != FIELD_SIZE-1) reveal_point(i-1, j+1);
    // left
    if(j != 0) reveal_point(i, j-1);
    // right
    if(j != FIELD_SIZE-1) reveal_point(i, j+1);
    // bottom left
    if(i != FIELD_SIZE-1 && j != 0) reveal_point(i+1, j-1);
    // bottom
    if(i != FIELD_SIZE-1) reveal_point(i+1, j);
    // bottom right
    if(i != FIELD_SIZE-1 && j != FIELD_SIZE-1) reveal_point(i+1, j+1);
  }
  return hfield[i][j] == '*';
}

void mark_mine(int i, int j) {
  int r = get_row(i), c = get_column(j);
  if(vfield[r][c] == '*') {
    vfield[r][c] = '-';
    return;
  }
  
  if(vfield[r][c] != '-')
    return;
  vfield[r][c] = '*';
}
