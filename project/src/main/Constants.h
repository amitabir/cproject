#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/* All the general constants required by several files are defined here */

// Dimentions of the board
#define BOARD_ROWS 7
#define BOARD_COLS 7

// Marks the content of board slots (the board is represented as two dimentional char array)
#define EMPTY_TILE '#'
#define WALL_TILE 'W'
#define CAT_TILE 'C' 
#define MOUSE_TILE 'M'
#define CHEESE_TILE 'P'

// Difficulty levels (number of steps to calculate)
#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 9

#endif /* CONSTANTS_H_ */

