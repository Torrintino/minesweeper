# Minesweeper in Text Mode written in C

This is a little - just for fun - exercise in C.
The size of the field and the amount of mines is defined in minesweeper.h.
Because the size is compiled and not given from user input, memory doesn't
need to be allocated dynamically.

The algorithm for generating random numbers is pretty poor and is subject
to change. The program doesn't accept invalid coordinates, however it uses
scanf, which is also to be changed.

The game expects to be executed in a UNIX environment, otherwise the clear
screen function will probably not work.

Please note, that the first point you reveal may be a mine, which is unfair.
The game could also generate situations, in which guessing is the only way
to win the game, even if all but two points are already revealed. Compared to
the original Minesweeper, this version doesn't have time tracking and high
scores.

Have fun :-)
