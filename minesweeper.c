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
  while(1) {
    int row, column;
    printf("\e[1;1H\e[2J");
    print_vfield();
    printf("Reveal a field (1) or mark a mine (2): ");
    char mode;
    scanf("%c", &mode);
    switch(mode) {
    case '1':
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
	print_vfield();
	printf("You won the game\n");
	return;
      }
      break;
    case '2':
      get_coordinates(&row, &column);
      if(row < 1 || row > FIELD_SIZE ||
	 column < 1 || column > FIELD_SIZE)
	continue;
      mark_mine(row-1, column-1);
      break;
    default:
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
