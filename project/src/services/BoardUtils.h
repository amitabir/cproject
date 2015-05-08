#ifndef BOARD_UTILS_H_
#define BOARD_UTILS_H_

#include "BoardPoint.h"

#define CANNOT_REACH_RESULT 1000

/* This function creates an empty gaming board using the BOARD_ROWS and BOARD_COLS constants and dynamical allocation. The board
is a two dimensional char array of BOARD_ROWS * BOARD_COLS. The function returns this empty board. */
char** createBoard();

/* Calculates and returns the shortest distance on the grid between the origin and destination points, taking into account the walls and cheese.
For the mouse (specified with the flag isMouse), the cat must also be taken into account because the mouse cannot go through any tile surrounding the cat.
The functions uses BFS algorithm to find the shorteset distance between the two points. 
The grid is made into a graph by setting all tiles as the nodes and there is an edge for every adjacent tiles (not diagonally). So the graph has n^2 nodes
and n^2 edges, since there is an edge only for adjacnet tiles. We thus get a BFS complexity of O(|V|+|E|) = n^2.
*/
int calcShortestDistance(char **board, BoardPoint origin, BoardPoint destination, BoardPoint catPoint, BoardPoint cheesePoint, int isMouse);

/* This function receives a two dimensional char array which represents the board and frees it. */
void freeBoard(char **board);

#endif /* BOARD_UTILS_H_ */
