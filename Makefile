SOURCE = minesweeper.c field.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: minesweeper

minesweeper: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $@

clean:
	rm -rf *.o

run: minesweeper
	./minesweeper
