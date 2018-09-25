# Minesweeper in Text Mode written in C

This is a little - just for fun - exercise in C.
The size of the field and the amount of mines is defined in minesweeper.h.
Because the size is compiled and not given from user input, memory doesn't
need to be allocated dynamically.

Some extensions that might come in the future:
* Using escape sequences to not constantly reprint the whole board and add a
  timer
* A highscore
* Some sort of command line configuration or similar, so that the board size
  and amount of mines does not need to be compiled
* Modes with different rules
* Hotkeys or something similar to improve controls
* Colors for various numbers
