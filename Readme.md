# Minesweeper in Text Mode written in C

This is a little - just for fun - exercise in C.
The size of the field and the amount of mines is defined in minesweeper.h.
Because the size is compiled and not given from user input, memory doesn't
need to be allocated dynamically.

The game expects to be executed in a UNIX environment, otherwise the clear
screen function will probably not work.
