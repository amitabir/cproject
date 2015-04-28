#ifndef BOARD_UTILS_H_
#define BOARD_UTILS_H_

#include "BoardPoint.h"

#define CANNOT_REACH_RESULT -1

char** createBoard();
int calcRealDistance(char **board, BoardPoint origin, BoardPoint destination, BoardPoint catPoint, int isMouse);
float calcOptDistance(BoardPoint point1, BoardPoint point2);
void freeBoard(char **board);

#endif /* BOARD_UTILS_H_ */
