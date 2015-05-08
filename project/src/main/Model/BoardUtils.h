#ifndef BOARD_UTILS_H_
#define BOARD_UTILS_H_

#include "BoardPoint.h"

#define CANNOT_REACH_RESULT -1

/* This function creates an empty gaming board using the BOARD_ROWS and BOARD_COLS constants and dynamical allocation. The board
is a two dimensional char array of BOARD_ROWS * BOARD_COLS. The function returns this empty board. */
char** createBoard();

/* This function uses the BFS algorithm to calculate the actual distance between an origin point and a destination point.
Some constraints may be added to the board depends on the isMouse int value. The distance is returned. */
int calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, BoardPoint catPoint, int isMouse);// TODO

/* This function receives two points and calculates and returns the optimal distance between them, i.e. with no walls, cat, mouse or cheese. */
float calcOptDistance(BoardPoint point1, BoardPoint point2);

/* This function receives a two dimensional char array which represents the board and frees it. */
void freeBoard(char **board);

#endif /* BOARD_UTILS_H_ */
