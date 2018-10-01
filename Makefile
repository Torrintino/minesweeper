SOURCE = minesweeper.c field.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: minesweeper

minesweeper: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $@

debug: $(SOURCE)
	$(CC) $(CFLAGS) -ggdb -static $(SOURCE) -o $@

clean:
	rm -rf *.o minesweeper debug

run: minesweeper
	./minesweeper
