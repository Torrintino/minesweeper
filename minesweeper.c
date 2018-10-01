#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minesweeper.h"
#include "field.h"

int get_coordinates(int* row, int* column) {
  printf("Row: ");
  scanf("%d", row);
  printf("Column: ");
  scanf("%d", column);
  
  if(*row < 1 || *row > ROWS ||
     *column < 1 || *column > COLS)
    return 0;
  return 1;
}

void play() {
  int mines_left = MINE_COUNT;
  while(1) {
    int row, column;
    int mode;

    print_board(mines_left);
    printf("Reveal a field (1) or mark a mine (2): ");
    scanf("%d", &mode);
    switch(mode) {
    case 1: // Reveal point
      if(!get_coordinates(&row, &column))
	continue;
      if(reveal_point(row-1, column-1)) {
	printf("\n");
	print_vfield();
	printf("\nYou lost the game\n");
	return;
      }
      if(REVEALED_POINTS == ROWS * COLS - MINE_COUNT) {
	printf("\n");
	print_vfield();
	printf("\nYou won the game\n");
	return;
      }
      break;

    case 2: // Mark mine
      if(!get_coordinates(&row, &column))
	continue;
      int status = mark_mine(row-1, column-1);
      if(status == 1) {
	mines_left--;
      } else if(!status) {
	mines_left++;
      }
      break;

    default: // Invalid input
      continue;
    }
  }
}


int main(int argc, char* argv[]) {
  if(argc == 1) {
    set_size(ROWS_SMALL, COLS_SMALL, MINES_SMALL);
  } else if(argc == 2) {
    if(!strcmp(argv[1], "small")) {
      set_size(ROWS_SMALL, COLS_SMALL, MINES_SMALL);
    } else if (!strcmp(argv[1], "medium")) {
      set_size(ROWS_MEDIUM, COLS_MEDIUM, MINES_MEDIUM);
    } else if (!strcmp(argv[1], "large")) {
      set_size(ROWS_LARGE, COLS_LARGE, MINES_LARGE);
    } else {
      fprintf(stderr, "Invalid arguments\n");
      return 1;
    }
  }
  else {
    fprintf(stderr, "Invalid arguments\n");
    return 1;
  }
  
  int row, column;
  if(!init_vfield(8)) {
    fprintf(stderr, "Allocation error\n");
    return EXIT_FAILURE;
  }
  do {
    print_board(MINE_COUNT);
    printf("Reveal a field\n");
  } while(!get_coordinates(&row, &column));
  if(!init_hfield(row-1, column-1)) {
    fprintf(stderr, "Allocation error\n");
    return EXIT_FAILURE;
  }
  reveal_point(row-1, column-1);
  play();

  destroy_hfield();
  destroy_vfield();
  return EXIT_SUCCESS;
}

void print_board(int mines_left) {
  printf("\e[1;1H\e[2J");
  printf("Mines left: %d\n\n", mines_left);
  print_vfield();
}
