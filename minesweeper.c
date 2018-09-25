#include <stdio.h>
#include <stdlib.h>

#include "minesweeper.h"
#include "field.h"

void get_coordinates(int* row, int* column) {
  printf("Row: ");
  scanf("%d", row);
  printf("Column: ");
  scanf("%d", column);
}

void play() {
  int mines_left = MINE_COUNT;
  while(1) {
    int row, column;
    printf("\e[1;1H\e[2J");
    printf("Mines left: %d\n\n", mines_left);
    print_vfield();
    printf("Reveal a field (1) or mark a mine (2): ");
    char mode;
    scanf("%c", &mode);
    switch(mode) {

    case '1': // Reveal point
      get_coordinates(&row, &column);
      if(row < 1 || row > FIELD_SIZE ||
	 column < 1 || column > FIELD_SIZE)
	continue;
      if(reveal_point(row-1, column-1)) {
	print_vfield();
	printf("You lost the game\n");
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
      get_coordinates(&row, &column);
      if(row < 1 || row > FIELD_SIZE ||
	 column < 1 || column > FIELD_SIZE)
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
  init_hfield();
  init_vfield();
  REVEALED_POINTS = 0;
  play();
  return 0;
}
