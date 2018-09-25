#include <stdio.h>
#include <stdlib.h>

#include "minesweeper.h"
#include "field.h"

int get_coordinates(int* row, int* column) {
  printf("Row: ");
  scanf("%d", row);
  printf("Column: ");
  scanf("%d", column);
  
  if(*row < 1 || *row > FIELD_SIZE ||
     *column < 1 || *column > FIELD_SIZE)
    return 0;
  return 1;
}

void play() {
  int mines_left = MINE_COUNT;
  while(1) {
    int row, column;
    char mode;

    print_board(mines_left);
    printf("Reveal a field (1) or mark a mine (2): ");
    scanf("%c", &mode);
    switch(mode) {
    case '1': // Reveal point
      if(!get_coordinates(&row, &column))
	continue;
      if(reveal_point(row-1, column-1)) {
	printf("\n");
	print_vfield();
	printf("\nYou lost the game\n");
	return;
      }
      if(REVEALED_POINTS == (FIELD_SIZE * FIELD_SIZE) - MINE_COUNT) {
	printf("\n");
	print_vfield();
	printf("\nYou won the game\n");
	return;
      }
      break;

    case '2': // Mark mine
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


int main() {
  int row, column;
  init_vfield();
  do {
    print_board(MINE_COUNT);
    printf("Reveal a field\n");
  } while(!get_coordinates(&row, &column));
  init_hfield(row-1, column-1);
  reveal_point(row-1, column-1);
  play();
  return 0;
}

void print_board(int mines_left) {
  printf("\e[1;1H\e[2J");
  printf("Mines left: %d\n\n", mines_left);
  print_vfield();
}
